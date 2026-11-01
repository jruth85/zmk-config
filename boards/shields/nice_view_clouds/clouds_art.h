/*
 * Drawing for the nice_view_clouds screens. Pure C, no LVGL or ZMK, so it can
 * also be built on a PC to preview the screens.
 *
 * Everything is drawn in portrait: NVC_W x NVC_H, origin at the top left,
 * one byte per pixel (0 = background, 1 = ink).
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>

#define NVC_W 68
#define NVC_H 160
#define NVC_MAX_LAYERS 6

typedef uint8_t nvc_fb_t[NVC_H][NVC_W];

struct nvc_status {
    uint8_t battery;  /* 0-100 */
    bool charging;
    bool usb;         /* left half: output is USB rather than Bluetooth */
    int profile;      /* left half: Bluetooth profile, 0-based */
    bool connected;   /* left: host connected; right: linked to the left half */
};

void nvc_clear(nvc_fb_t fb);

/* Left half: battery, output, and the layer list (filled box = active layer). */
void nvc_draw_status_bar(nvc_fb_t fb, const struct nvc_status *s, bool central);
void nvc_draw_layers(nvc_fb_t fb, const char *const names[], int count, int active);

/* Right half: mountain with clouds drifting behind it.
 * nvc_scene_step() advances the clouds one frame; speed16 is a multiplier in
 * sixteenths (16 = normal speed). */
void nvc_scene_step(int speed16);
void nvc_draw_scene(nvc_fb_t fb);
