/*
 * Corne (crkbd) Vial keymap
 *   - Layers on G (NUM) and B (NAV) and on the right thumbs
 *   - Shift + a layer-tap key always types the key
 *   - OLED: layer list + one-shot timer on the left, mountain and
 *     clouds on the right (same as the Lily58)
 *
 * Copyright 2019 @foostan, 2020 Drashna Jaelre <@drashna> - GPL-2.0-or-later
 */

#include QMK_KEYBOARD_H
#ifdef QMK_SETTINGS
#    include "qmk_settings.h"
#endif

/* Default keymap, generated from corne.vil. This is what the board falls
 * back to if a reflash wipes the layout saved in Vial. Macros and QMK
 * Settings are not included: restore those by loading the .vil. */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: BASE
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | GEsc |  Q   |  W   |  E   |  R   |  T   |                    |  Y   |  U   |  I   |  O   |  P   | BkSp |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Ins  |  A   |  S   |  D   |  F   |  G   |                    |  H   |  J   |  K   |  L   |  ;   |  '   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |LCtrl |  Z   |  X   |  C   |  V   |  B   |                    |  N   |  M   |  ,   |  .   |  /   |  \   |
     * `-----------------------------------------'                    `-----------------------------------------'
     *                      ,--------------------.                    ,--------------------.
     *                      | Del  | LGUI |OSSft |                    |Space | Tab  |Enter |
     *                      |      |      |      |                    | FUN  | SYM  | MOUS |
     *                      `--------------------'                    `--------------------'
     */
    [0] = LAYOUT_split_3x6_3(
        QK_GESC,        KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,              KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSPC,       
        KC_INS,         KC_A,           KC_S,           KC_D,           KC_F,           LT(3, KC_G),       KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,       
        KC_LCTL,        KC_Z,           KC_X,           KC_C,           KC_V,           LT(2, KC_B),       KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_BSLS,       
                                                        KC_DEL,         KC_LGUI,        OSM(MOD_LSFT),     LT(4, KC_SPC),  LT(1, KC_TAB),  LT(5, KC_ENT)
    ),
    /* 1: SYM
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |  ^   |  &   |  *   |  (   |  )   |                    |      |      |      |      |      |(trns)|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |  !   |  @   |  #   |  $   |  %   |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |  +   |  =   |  _   |  -   |                    |      |      |      |      |      |      |
     * `-----------------------------------------'                    `-----------------------------------------'
     *                      ,--------------------.                    ,--------------------.
     *                      |  (   |  )   | Caps |                    |      |      |      |
     *                      `--------------------'                    `--------------------'
     */
    [1] = LAYOUT_split_3x6_3(
        XXXXXXX,        LSFT(KC_6),     LSFT(KC_7),     LSFT(KC_8),     LSFT(KC_9),     LSFT(KC_0),        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        _______,       
        XXXXXXX,        LSFT(KC_1),     LSFT(KC_2),     LSFT(KC_3),     LSFT(KC_4),     LSFT(KC_5),        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,       
        XXXXXXX,        XXXXXXX,        LSFT(KC_EQL),   KC_EQL,         LSFT(KC_MINS),  KC_MINS,           XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,       
                                                        LSFT(KC_9),     LSFT(KC_0),     KC_CAPS,           XXXXXXX,        XXXXXXX,        XXXXXXX
    ),
    /* 2: NAV
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    | Home |  Up  | PgUp |      |      |(trns)|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    | Left | Down |Right |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    | End  | Down | PgDn |      |      |      |
     * `-----------------------------------------'                    `-----------------------------------------'
     *                      ,--------------------.                    ,--------------------.
     *                      |      |      |      |                    |      |      |      |
     *                      `--------------------'                    `--------------------'
     */
    [2] = LAYOUT_split_3x6_3(
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,      KC_HOME,   KC_UP,     KC_PGUP,   XXXXXXX,   XXXXXXX,   _______,  
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,      KC_LEFT,   KC_DOWN,   KC_RIGHT,  XXXXXXX,   XXXXXXX,   XXXXXXX,  
        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,      KC_END,    KC_DOWN,   KC_PGDN,   XXXXXXX,   XXXXXXX,   XXXXXXX,  
                                         XXXXXXX,   XXXXXXX,   XXXXXXX,      XXXXXXX,   XXXXXXX,   XXXXXXX
    ),
    /* 3: NUM
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | Boot |      |      |      |      |      |                    |  7   |  8   |  9   |  [   |  ]   |(trns)|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |  4   |  5   |  6   |  {   |  }   |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |  1   |  2   |  3   |  (   |  )   |      |
     * `-----------------------------------------'                    `-----------------------------------------'
     *                      ,--------------------.                    ,--------------------.
     *                      |      |      |      |                    |  0   |  .   |  -   |
     *                      `--------------------'                    `--------------------'
     */
    [3] = LAYOUT_split_3x6_3(
        QK_BOOT,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,           KC_P7,          KC_P8,          KC_P9,          KC_LBRC,        KC_RBRC,        _______,       
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,           KC_P4,          KC_P5,          KC_P6,          LSFT(KC_LBRC),  LSFT(KC_RBRC),  XXXXXXX,       
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,           KC_P1,          KC_P2,          KC_P3,          LSFT(KC_9),     LSFT(KC_0),     XXXXXXX,       
                                                        XXXXXXX,        XXXXXXX,        XXXXXXX,           KC_P0,          KC_PDOT,        KC_PMNS
    ),
    /* 4: FUN
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | Mac0 |  F1  |  F2  |  F3  |  F4  |  F5  |                    |      |      |      |      |      |(trns)|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Mac1 |  F6  |  F7  |  F8  |  F9  | F10  |                    |      |RShift|RCtrl | RAlt | RGUI |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Mac2 |PrtSc |ScrLk |Pause | F11  | F12  |                    |      |      |      |      |      |      |
     * `-----------------------------------------'                    `-----------------------------------------'
     *                      ,--------------------.                    ,--------------------.
     *                      |      |      |      |                    |      |      |      |
     *                      `--------------------'                    `--------------------'
     */
    [4] = LAYOUT_split_3x6_3(
        QK_MACRO_0,  KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,          XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     _______,    
        QK_MACRO_1,  KC_F6,       KC_F7,       KC_F8,       KC_F9,       KC_F10,         XXXXXXX,     KC_RSFT,     KC_RCTL,     KC_RALT,     KC_RGUI,     XXXXXXX,    
        QK_MACRO_2,  KC_PSCR,     KC_SCRL,     KC_PAUS,     KC_F11,      KC_F12,         XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,    
                                               XXXXXXX,     XXXXXXX,     XXXXXXX,        XXXXXXX,     XXXXXXX,     XXXXXXX
    ),
    /* 5: MOUS
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      | WhUp | MsUp |WhLft |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |MsLft | MsDn |MsRgt |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      | WhDn | MsDn |WhRgt |      |      |                    |      |      |      |      |      |      |
     * `-----------------------------------------'                    `-----------------------------------------'
     *                      ,--------------------.                    ,--------------------.
     *                      | Btn1 | Btn2 | Btn3 |                    |      |      |      |
     *                      `--------------------'                    `--------------------'
     */
    [5] = LAYOUT_split_3x6_3(
        XXXXXXX,  MS_WHLU,  MS_UP,    MS_WHLL,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, 
        XXXXXXX,  MS_LEFT,  MS_DOWN,  MS_RGHT,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, 
        XXXXXXX,  MS_WHLD,  MS_DOWN,  MS_WHLR,  XXXXXXX,  XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, 
                                      MS_BTN1,  MS_BTN2,  MS_BTN3,     XXXXXXX,  XXXXXXX,  XXXXXXX
    ),
};

/* Shift + a layer-tap key always types the key, never the layer.
 * Shift+G -> G, Shift+B -> B, Shift+Tab -> back-tab, Shift+Space -> space. */
static keypos_t lt_shift_pos[4];
static uint16_t lt_shift_kc[4];

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    keypos_t k = record->event.key;
    if (record->event.pressed) {
        if (IS_QK_LAYER_TAP(keycode) && ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)) {
            for (int i = 0; i < 4; i++) {
                if (lt_shift_kc[i] == KC_NO) {
                    lt_shift_pos[i] = k;
                    lt_shift_kc[i]  = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
                    register_code(lt_shift_kc[i]);
                    return false;
                }
            }
        }
    } else {
        /* release whatever this key sent, even if Shift was let go first */
        for (int i = 0; i < 4; i++) {
            if (lt_shift_kc[i] != KC_NO && lt_shift_pos[i].row == k.row && lt_shift_pos[i].col == k.col) {
                unregister_code(lt_shift_kc[i]);
                lt_shift_kc[i] = KC_NO;
                return false;
            }
        }
    }
    return true;
}

#ifdef OLED_ENABLE
/* ===================================================================
 * OLED (portrait, 32 x 128 px, 5 chars x 16 lines)
 *
 * Status half (left, plugged into USB):
 *   One line per layer: solid box = current layer,
 *   checkered box = one-shot layer waiting for its next key.
 *   Bottom: OSL tag + millisecond timer while a one-shot is pending,
 *   kept on screen for 1 s after it ends.
 * Other half: small mountain, clouds drifting behind it, faster as
 *   you type faster (needs WPM_ENABLE + SPLIT_WPM_ENABLE).
 * =================================================================== */

/* 4 characters max. Index = layer number. */
static const char *const layer_names[] = {"BASE", "SYM", "NAV", "NUM", "FUN", "MOUS"};
#define LAYER_NAME_COUNT ((uint8_t)(sizeof(layer_names) / sizeof(layer_names[0])))

#ifndef SCREEN_SLEEP_MS
#    define SCREEN_SLEEP_MS 60000
#endif

/* If a screen comes out upside down:
 *   left (status) screen  -> change OLED_ROTATION_270 to OLED_ROTATION_90
 *   right (scene) screen  -> uncomment SCENE_FLIP */
#define STATUS_ROTATION OLED_ROTATION_270
// #define SCENE_FLIP

/* The Corne's keyboard-level code ignores oled_init_user(), so the
 * status half is switched to portrait by re-initialising its screen. */
void keyboard_post_init_user(void) {
    if (is_keyboard_master()) {
        oled_init(STATUS_ROTATION);
    }
}

/* ---------- status half ---------- */

enum { BOX_OUTLINE, BOX_FILLED, BOX_CHECKER };

/* 5x7 box in the first character column of a text row, matching the
 * letter height; column 5 stays blank as a gap before the name. */
static void draw_layer_box(uint8_t row, uint8_t mode) {
    uint8_t y0 = row * 8;
    for (uint8_t dy = 0; dy < 7; dy++) {
        for (uint8_t dx = 0; dx < 5; dx++) {
            bool edge = dx == 0 || dy == 0 || dx == 4 || dy == 6;
            bool on;
            switch (mode) {
                case BOX_FILLED:  on = true; break;
                case BOX_CHECKER: on = edge || !((dx + dy) & 1); break;
                default:          on = false; break; /* inactive layer: blank */
            }
            oled_write_pixel(dx, y0 + dy, on);
        }
    }
}

/* Writes exactly `width` characters at (col,row), padding with spaces. */
static void write_padded(uint8_t col, uint8_t row, uint8_t width, const char *text, bool invert) {
    char buf[6] = "     ";
    for (uint8_t i = 0; i < width && text[i]; i++) buf[i] = text[i];
    buf[width] = '\0';
    oled_set_cursor(col, row);
    oled_write(buf, invert);
}

static void render_status(void) {
    static uint32_t os_start = 0;
    static uint32_t os_end   = 0;
    static bool     os_was   = false;
    static uint8_t  os_prev  = 0;
    static uint16_t shown_ms = 0;

    bool    oneshot = is_oneshot_layer_active();
    uint8_t os_lyr  = get_oneshot_layer();

    /* Solid box = highest layer not counting a pending one-shot layer */
    layer_state_t held = layer_state;
    if (oneshot) held &= ~((layer_state_t)1 << os_lyr);
    uint8_t layer = get_highest_layer(held | default_layer_state);

    for (uint8_t i = 0; i < LAYER_NAME_COUNT && i < 6; i++) {
        uint8_t row  = i * 2;
        uint8_t mode = BOX_OUTLINE;
        if (oneshot && i == os_lyr) {
            mode = BOX_CHECKER;
        } else if (i == layer) {
            mode = BOX_FILLED;
        }
        draw_layer_box(row, mode);
        write_padded(1, row, 4, layer_names[i], false);
    }

    /* One-shot timer. Restarts on a new one-shot (or a chained one);
     * remembers when the one-shot ended so the last value can linger. */
    if (oneshot && (!os_was || os_lyr != os_prev)) os_start = timer_read32();
    if (!oneshot && os_was) os_end = timer_read32();
    bool just_ended = !oneshot && os_was;
    os_was  = oneshot;
    os_prev = os_lyr;

#if defined(QMK_SETTINGS)
    uint16_t timeout = QS_oneshot_timeout; /* live value from Vial's QMK Settings */
#elif defined(ONESHOT_TIMEOUT)
    uint16_t timeout = ONESHOT_TIMEOUT;
#else
    uint16_t timeout = 0;
#endif

    if (oneshot) {
        uint32_t elapsed = timer_elapsed32(os_start);
        if (timeout > 0) {
            /* time remaining before the one-shot times out */
            shown_ms = elapsed >= timeout ? 0 : (uint16_t)(timeout - elapsed);
        } else {
            /* no timeout set: how long it has been waiting */
            shown_ms = elapsed > 65535 ? 65535 : (uint16_t)elapsed;
        }
    }

    /* Show the time while the one-shot is pending and for 1 s after. */
    bool show_time = oneshot || just_ended || (os_end && timer_elapsed32(os_end) < 1000);

    write_padded(0, 12, 5, oneshot ? "OSL" : "", oneshot);
    if (show_time) {
        char     num[6];
        uint16_t v = shown_ms;
        for (int8_t i = 4; i >= 0; i--) {
            num[i] = (v || i == 4) ? (char)('0' + v % 10) : ' ';
            v /= 10;
        }
        num[5] = '\0';
        write_padded(0, 14, 5, num, false);
        write_padded(0, 15, 5, "   ms", false);
    } else {
        write_padded(0, 14, 5, "", false);
        write_padded(0, 15, 5, "", false);
    }
}

/* ---------- scene half: clouds behind a small mountain ---------- */

/* The Corne's keyboard code locks this half's screen to landscape, so the
 * portrait scene (32 x 128) is turned sideways here, pixel by pixel. */
static void scene_pixel(uint8_t px, uint8_t py, bool on) {
#ifdef SCENE_FLIP
    oled_write_pixel(127 - py, px, on);
#else
    oled_write_pixel(py, 31 - px, on);
#endif
}

/* Mountain ridge: y of the ridge line at each x (two peaks). */
static const uint8_t ridge_pts[][2] = {{0, 112}, {7, 103}, {11, 107}, {19, 92}, {26, 103}, {31, 99}};
#define RIDGE_N ((uint8_t)(sizeof(ridge_pts) / sizeof(ridge_pts[0])))

static uint8_t ridge_y(int16_t x) {
    if (x < 0) x = 0;
    if (x > 31) x = 31;
    for (uint8_t i = 0; i + 1 < RIDGE_N; i++) {
        int16_t x0 = ridge_pts[i][0], x1 = ridge_pts[i + 1][0];
        if (x >= x0 && x <= x1) {
            int16_t y0 = ridge_pts[i][1], y1 = ridge_pts[i + 1][1];
            return (uint8_t)(y0 + (y1 - y0) * (x - x0) / (x1 - x0));
        }
    }
    return 127;
}

/* Cloud shapes, 16 px wide; bit 15 = leftmost pixel. */
static const uint16_t cloud_big[]   = {0x0300, 0x0FD8, 0x1FFC, 0x7FFE, 0xFFFF, 0xFFFF, 0x7FFE, 0x1FF8};
static const uint16_t cloud_mid[]   = {0x0E00, 0x3FB0, 0x7FF8, 0xFFFC, 0x7FF8, 0x3FF0};
static const uint16_t cloud_small[] = {0x1C00, 0x7F00, 0xFFC0, 0x7F80};

typedef struct {
    const uint16_t *shape;
    uint8_t         rows;
    uint8_t         y;     /* top edge */
    uint8_t         speed; /* sixteenths of a pixel per frame at 0 WPM */
    int16_t         pos;   /* left edge, in sixteenths of a pixel */
} cloud_t;

/* Lower clouds move faster (closer), the lowest one passes behind the peak. */
static cloud_t clouds[] = {
    {cloud_small, 4, 4, 2, 6 * 16},
    {cloud_big, 8, 14, 3, 20 * 16},
    {cloud_mid, 6, 30, 4, -4 * 16},
    {cloud_big, 8, 44, 4, 14 * 16},
    {cloud_small, 4, 60, 5, 26 * 16},
    {cloud_mid, 6, 70, 6, 2 * 16},
    {cloud_big, 8, 86, 7, 22 * 16},
};
#define CLOUD_N ((uint8_t)(sizeof(clouds) / sizeof(clouds[0])))
#define CLOUD_W 16

static bool cloud_has(const cloud_t *c, int16_t lx, int16_t ly) {
    if (lx < 0 || lx >= CLOUD_W || ly < 0 || ly >= c->rows) return false;
    return (c->shape[ly] >> (15 - lx)) & 1;
}

/* Outline only: a cloud pixel that has an empty neighbour. */
static bool cloud_pixel(uint8_t x, uint8_t y) {
    for (uint8_t i = 0; i < CLOUD_N; i++) {
        const cloud_t *c  = &clouds[i];
        int16_t        lx = (int16_t)x - (c->pos >> 4);
        int16_t        ly = (int16_t)y - c->y;
        if (!cloud_has(c, lx, ly)) continue;
        if (!cloud_has(c, lx - 1, ly) || !cloud_has(c, lx + 1, ly) || !cloud_has(c, lx, ly - 1) || !cloud_has(c, lx, ly + 1)) return true;
    }
    return false;
}

static bool mountain_pixel(uint8_t x, uint8_t y, bool *inside) {
    uint8_t ry = ridge_y(x);
    *inside    = y >= ry;
    if (!*inside) return false;
    if (y == 127) return true;                                  /* ground */
    if (y == ry || y < ridge_y(x - 1) || y < ridge_y(x + 1)) return true; /* outline */
    if (y <= 97 && !(y == 97 && (x & 1))) return true;           /* snow on the tall peak */
    /* sparse dot texture so the mountain reads as solid rock */
    return (y % 3 == 0) && ((x + y) % 4 == 0);
}

static void render_scene(void) {
    static uint32_t frame_timer = 0;
    static bool     first       = true;

    if (!first && timer_elapsed32(frame_timer) < 90) return; /* ~11 fps */
    first       = false;
    frame_timer = timer_read32();

    /* Speed multiplier from typing speed: 1x idle, ~4x at 75 WPM */
    uint16_t mult16 = 16;
#ifdef WPM_ENABLE
    mult16 += get_current_wpm() * 16 / 25;
#endif
    for (uint8_t i = 0; i < CLOUD_N; i++) {
        clouds[i].pos -= (int16_t)((clouds[i].speed * mult16) >> 4); /* drift right to left */
        if ((clouds[i].pos >> 4) < -CLOUD_W) clouds[i].pos = 32 * 16;
    }

    for (uint8_t y = 0; y < 128; y++) {
        for (uint8_t x = 0; x < 32; x++) {
            bool inside;
            bool on = mountain_pixel(x, y, &inside);
            if (!inside) on = cloud_pixel(x, y);
            scene_pixel(x, y, on);
        }
    }
}

/* ---------- entry point ---------- */

bool oled_task_user(void) {
    if (last_input_activity_elapsed() > SCREEN_SLEEP_MS) {
        oled_off();
        return false;
    }
    oled_on();
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_scene();
    }
    return false;
}

#endif // OLED_ENABLE
