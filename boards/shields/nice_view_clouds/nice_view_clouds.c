/*
 * nice!view screens for the Corne.
 *
 *   Left half (central):     battery, output (USB / BT profile, filled = connected)
 *                            and the layer list (filled box = active layer).
 *   Right half (peripheral): battery, link to the left half (filled dot = linked)
 *                            and a mountain with clouds drifting behind it. The
 *                            clouds speed up while you type on that half and stop
 *                            when the keyboard goes idle.
 *
 * Drawing lives in clouds_art.c; this file connects it to ZMK and LVGL.
 */

#include <zephyr/kernel.h>
#include <lvgl.h>

#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/battery.h>
#include <zmk/usb.h>
#include <zmk/activity.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/events/activity_state_changed.h>

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
#define NVC_CENTRAL 1
#include <zmk/keymap.h>
#include <zmk/endpoints.h>
#include <zmk/ble.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/endpoint_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#else
#define NVC_CENTRAL 0
#include <zmk/split/bluetooth/peripheral.h>
#include <zmk/events/split_peripheral_status_changed.h>
#include <zmk/events/position_state_changed.h>
#endif

#include "clouds_art.h"

#define LS_W 160 /* the panel is landscape; the image is drawn in portrait */
#define LS_H 68

static lv_obj_t *canvas;
static lv_color_t cbuf[LS_W * LS_H];
static nvc_fb_t fb;
static struct nvc_status status;

/* Copy the portrait image to the landscape panel, turned a quarter turn the
 * same way ZMK's stock nice!view screen is. */
static void blit(void) {
    lv_color_t ink = IS_ENABLED(CONFIG_NICE_VIEW_CLOUDS_INVERTED) ? lv_color_white() : lv_color_black();
    lv_color_t paper = IS_ENABLED(CONFIG_NICE_VIEW_CLOUDS_INVERTED) ? lv_color_black() : lv_color_white();
    for (int y = 0; y < NVC_H; y++) {
        for (int x = 0; x < NVC_W; x++) {
            int lx = LS_W - 1 - y, ly = x;
            if (IS_ENABLED(CONFIG_NICE_VIEW_CLOUDS_FLIP)) {
                lx = LS_W - 1 - lx;
                ly = LS_H - 1 - ly;
            }
            cbuf[ly * LS_W + lx] = fb[y][x] ? ink : paper;
        }
    }
    lv_obj_invalidate(canvas);
}

/* ---------- left half: status and layers ---------- */
#if NVC_CENTRAL

static void redraw(void) {
    const char *names[NVC_MAX_LAYERS];
    int count = 0;
    for (zmk_keymap_layer_index_t i = 0; i < ZMK_KEYMAP_LAYERS_LEN && count < NVC_MAX_LAYERS; i++) {
        const char *name = zmk_keymap_layer_name(zmk_keymap_layer_index_to_id(i));
        if (name == NULL || name[0] == '\0') {
            break; /* stop at the first unnamed (e.g. reserved Studio) layer */
        }
        names[count++] = name;
    }
    nvc_clear(fb);
    nvc_draw_status_bar(fb, &status, true);
    nvc_draw_layers(fb, names, count, zmk_keymap_highest_layer_active());
    blit();
}

struct output_state {
    bool usb;
    int profile;
    bool connected;
};

static struct output_state output_get(const zmk_event_t *eh) {
    struct zmk_endpoint_instance ep = zmk_endpoints_selected();
    bool usb = ep.transport == ZMK_TRANSPORT_USB;
    return (struct output_state){
        .usb = usb,
        .profile = zmk_ble_active_profile_index(),
        .connected = usb ? zmk_usb_is_powered() : zmk_ble_active_profile_is_connected(),
    };
}

static void output_update(struct output_state s) {
    status.usb = s.usb;
    status.profile = s.profile;
    status.connected = s.connected;
    redraw();
}

ZMK_DISPLAY_WIDGET_LISTENER(nvc_output, struct output_state, output_update, output_get)
ZMK_SUBSCRIPTION(nvc_output, zmk_endpoint_changed);
ZMK_SUBSCRIPTION(nvc_output, zmk_ble_active_profile_changed);
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
ZMK_SUBSCRIPTION(nvc_output, zmk_usb_conn_state_changed);
#endif

struct layer_state {
    uint8_t active;
};

static struct layer_state layer_get(const zmk_event_t *eh) {
    return (struct layer_state){.active = zmk_keymap_highest_layer_active()};
}

static void layer_update(struct layer_state s) {
    ARG_UNUSED(s);
    redraw();
}

ZMK_DISPLAY_WIDGET_LISTENER(nvc_layer, struct layer_state, layer_update, layer_get)
ZMK_SUBSCRIPTION(nvc_layer, zmk_layer_state_changed);

/* ---------- right half: link status and the animated scene ---------- */
#else

#define WINDOW_FRAMES 20 /* keypress rate is averaged over this many frames */

static atomic_t presses;
static uint8_t window[WINDOW_FRAMES];
static uint8_t window_pos;
static bool animating;

static void redraw(void) {
    nvc_clear(fb);
    nvc_draw_status_bar(fb, &status, false);
    nvc_draw_scene(fb);
    blit();
}

/* Speed multiplier in sixteenths: 1x idle, faster the more you type on this
 * half (this half only sees its own keys, so the rate is roughly half your
 * total typing speed). */
static int speed16(void) {
    window[window_pos] = (uint8_t)MIN(atomic_set(&presses, 0), 255);
    window_pos = (window_pos + 1) % WINDOW_FRAMES;
    int sum = 0;
    for (int i = 0; i < WINDOW_FRAMES; i++) {
        sum += window[i];
    }
    return 16 + MIN(sum, 30) * 3;
}

static void frame_cb(struct k_work *work);
static K_WORK_DELAYABLE_DEFINE(frame_work, frame_cb);

static void frame_cb(struct k_work *work) {
    nvc_scene_step(speed16());
    redraw();
    if (animating) {
        k_work_schedule_for_queue(zmk_display_work_q(), &frame_work,
                                  K_MSEC(CONFIG_NICE_VIEW_CLOUDS_FRAME_MS));
    }
}

static int press_listener(const zmk_event_t *eh) {
    const struct zmk_position_state_changed *ev = as_zmk_position_state_changed(eh);
    if (ev != NULL && ev->state) {
        atomic_inc(&presses);
    }
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(nvc_presses, press_listener);
ZMK_SUBSCRIPTION(nvc_presses, zmk_position_state_changed);

struct link_state {
    bool connected;
};

static struct link_state link_get(const zmk_event_t *eh) {
    return (struct link_state){.connected = zmk_split_bt_peripheral_is_connected()};
}

static void link_update(struct link_state s) {
    status.connected = s.connected;
    redraw();
}

ZMK_DISPLAY_WIDGET_LISTENER(nvc_link, struct link_state, link_update, link_get)
ZMK_SUBSCRIPTION(nvc_link, zmk_split_peripheral_status_changed);

/* Animate only while the keyboard is active; the last frame stays on the
 * panel (it needs no power to hold an image). */
struct activity {
    bool active;
};

static struct activity activity_get(const zmk_event_t *eh) {
    return (struct activity){.active = zmk_activity_get_state() == ZMK_ACTIVITY_ACTIVE};
}

static void activity_update(struct activity s) {
    animating = s.active;
    if (animating) {
        k_work_schedule_for_queue(zmk_display_work_q(), &frame_work, K_NO_WAIT);
    } else {
        k_work_cancel_delayable(&frame_work);
    }
}

ZMK_DISPLAY_WIDGET_LISTENER(nvc_activity, struct activity, activity_update, activity_get)
ZMK_SUBSCRIPTION(nvc_activity, zmk_activity_state_changed);

#endif /* NVC_CENTRAL */

/* ---------- battery (both halves) ---------- */

struct battery_state {
    uint8_t level;
    bool charging;
};

static struct battery_state battery_get(const zmk_event_t *eh) {
    const struct zmk_battery_state_changed *ev = as_zmk_battery_state_changed(eh);
    return (struct battery_state){
        .level = (ev != NULL) ? ev->state_of_charge : zmk_battery_state_of_charge(),
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
        .charging = zmk_usb_is_powered(),
#endif
    };
}

static void battery_update(struct battery_state s) {
    status.battery = s.level;
    status.charging = s.charging;
    redraw();
}

ZMK_DISPLAY_WIDGET_LISTENER(nvc_battery, struct battery_state, battery_update, battery_get)
ZMK_SUBSCRIPTION(nvc_battery, zmk_battery_state_changed);
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
ZMK_SUBSCRIPTION(nvc_battery, zmk_usb_conn_state_changed);
#endif

/* ---------- screen ---------- */

lv_obj_t *zmk_display_status_screen(void) {
    lv_obj_t *screen = lv_obj_create(NULL);
    canvas = lv_canvas_create(screen);
    lv_canvas_set_buffer(canvas, cbuf, LS_W, LS_H, LV_IMG_CF_TRUE_COLOR);
    lv_obj_align(canvas, LV_ALIGN_TOP_LEFT, 0, 0);

    nvc_battery_init();
#if NVC_CENTRAL
    nvc_output_init();
    nvc_layer_init();
#else
    nvc_link_init();
    nvc_activity_init();
#endif
    return screen;
}
