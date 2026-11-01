/*
 * Drawing for the nice_view_clouds screens. See clouds_art.h.
 */
#include <string.h>

#include "clouds_art.h"

/* ---------- pixels and text ---------- */

static inline void px(nvc_fb_t fb, int x, int y, bool on) {
    if (x >= 0 && x < NVC_W && y >= 0 && y < NVC_H) {
        fb[y][x] = on ? 1 : 0;
    }
}

static void rect(nvc_fb_t fb, int x, int y, int w, int h, bool filled) {
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            if (filled || i == 0 || j == 0 || i == w - 1 || j == h - 1) {
                px(fb, x + i, y + j, true);
            }
        }
    }
}

/* Adafruit GFX classic 5x7 font (BSD licence), ' ' through '_'.
 * One byte per column, least significant bit at the top. */
static const uint8_t font5x7[][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x5F, 0x00, 0x00}, {0x00, 0x07, 0x00, 0x07, 0x00},
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, {0x24, 0x2A, 0x7F, 0x2A, 0x12}, {0x23, 0x13, 0x08, 0x64, 0x62},
    {0x36, 0x49, 0x56, 0x20, 0x50}, {0x00, 0x08, 0x07, 0x03, 0x00}, {0x00, 0x1C, 0x22, 0x41, 0x00},
    {0x00, 0x41, 0x22, 0x1C, 0x00}, {0x2A, 0x1C, 0x7F, 0x1C, 0x2A}, {0x08, 0x08, 0x3E, 0x08, 0x08},
    {0x00, 0x80, 0x70, 0x30, 0x00}, {0x08, 0x08, 0x08, 0x08, 0x08}, {0x00, 0x00, 0x60, 0x60, 0x00},
    {0x20, 0x10, 0x08, 0x04, 0x02}, {0x3E, 0x51, 0x49, 0x45, 0x3E}, {0x00, 0x42, 0x7F, 0x40, 0x00},
    {0x72, 0x49, 0x49, 0x49, 0x46}, {0x21, 0x41, 0x49, 0x4D, 0x33}, {0x18, 0x14, 0x12, 0x7F, 0x10},
    {0x27, 0x45, 0x45, 0x45, 0x39}, {0x3C, 0x4A, 0x49, 0x49, 0x31}, {0x41, 0x21, 0x11, 0x09, 0x07},
    {0x36, 0x49, 0x49, 0x49, 0x36}, {0x46, 0x49, 0x49, 0x29, 0x1E}, {0x00, 0x00, 0x14, 0x00, 0x00},
    {0x00, 0x40, 0x34, 0x00, 0x00}, {0x00, 0x08, 0x14, 0x22, 0x41}, {0x14, 0x14, 0x14, 0x14, 0x14},
    {0x00, 0x41, 0x22, 0x14, 0x08}, {0x02, 0x01, 0x59, 0x09, 0x06}, {0x3E, 0x41, 0x5D, 0x59, 0x4E},
    {0x7C, 0x12, 0x11, 0x12, 0x7C}, {0x7F, 0x49, 0x49, 0x49, 0x36}, {0x3E, 0x41, 0x41, 0x41, 0x22},
    {0x7F, 0x41, 0x41, 0x41, 0x3E}, {0x7F, 0x49, 0x49, 0x49, 0x41}, {0x7F, 0x09, 0x09, 0x09, 0x01},
    {0x3E, 0x41, 0x41, 0x51, 0x73}, {0x7F, 0x08, 0x08, 0x08, 0x7F}, {0x00, 0x41, 0x7F, 0x41, 0x00},
    {0x20, 0x40, 0x41, 0x3F, 0x01}, {0x7F, 0x08, 0x14, 0x22, 0x41}, {0x7F, 0x40, 0x40, 0x40, 0x40},
    {0x7F, 0x02, 0x1C, 0x02, 0x7F}, {0x7F, 0x04, 0x08, 0x10, 0x7F}, {0x3E, 0x41, 0x41, 0x41, 0x3E},
    {0x7F, 0x09, 0x09, 0x09, 0x06}, {0x3E, 0x41, 0x51, 0x21, 0x5E}, {0x7F, 0x09, 0x19, 0x29, 0x46},
    {0x26, 0x49, 0x49, 0x49, 0x32}, {0x03, 0x01, 0x7F, 0x01, 0x03}, {0x3F, 0x40, 0x40, 0x40, 0x3F},
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, {0x3F, 0x40, 0x38, 0x40, 0x3F}, {0x63, 0x14, 0x08, 0x14, 0x63},
    {0x03, 0x04, 0x78, 0x04, 0x03}, {0x61, 0x59, 0x49, 0x4D, 0x43}, {0x00, 0x7F, 0x41, 0x41, 0x41},
    {0x02, 0x04, 0x08, 0x10, 0x20}, {0x00, 0x41, 0x41, 0x41, 0x7F}, {0x04, 0x02, 0x01, 0x02, 0x04},
    {0x40, 0x40, 0x40, 0x40, 0x40},
};

/* Draws text at (x, y), each font pixel scale x scale. Lower case is shown as
 * upper case. Returns the x just past the text. */
static int text(nvc_fb_t fb, int x, int y, const char *s, int scale, bool on) {
    for (; *s; s++) {
        char c = *s;
        if (c >= 'a' && c <= 'z') {
            c = (char)(c - 'a' + 'A');
        }
        if (c < ' ' || c > '_') {
            c = '?';
        }
        const uint8_t *g = font5x7[c - ' '];
        for (int col = 0; col < 5; col++) {
            for (int row = 0; row < 7; row++) {
                if (g[col] & (1 << row)) {
                    for (int dy = 0; dy < scale; dy++) {
                        for (int dx = 0; dx < scale; dx++) {
                            px(fb, x + col * scale + dx, y + row * scale + dy, on);
                        }
                    }
                }
            }
        }
        x += 6 * scale;
    }
    return x;
}

static int text_width(const char *s, int scale) { return (int)strlen(s) * 6 * scale - scale; }

void nvc_clear(nvc_fb_t fb) { memset(fb, 0, sizeof(nvc_fb_t)); }

/* ---------- status bar (both halves) ---------- */

static void battery(nvc_fb_t fb, int x, int y, uint8_t level, bool charging) {
    rect(fb, x, y, 15, 9, false);                  /* body */
    rect(fb, x + 15, y + 2, 2, 5, true);           /* terminal */
    int fill = (level > 100 ? 100 : level) * 11 / 100;
    if (fill > 0) {
        rect(fb, x + 2, y + 2, fill, 5, true);
    }
    char buf[6];
    int n = 0;
    if (charging) {
        buf[n++] = '+';
    }
    if (level >= 100) {
        buf[n++] = '1';
        buf[n++] = '0';
        buf[n++] = '0';
    } else {
        if (level >= 10) {
            buf[n++] = (char)('0' + level / 10);
        }
        buf[n++] = (char)('0' + level % 10);
    }
    if (!charging) {
        buf[n++] = '%'; /* "+" already marks it as a battery reading */
    }
    buf[n] = '\0';
    text(fb, x + 20, y + 1, buf, 1, true);
}

void nvc_draw_status_bar(nvc_fb_t fb, const struct nvc_status *s, bool central) {
    battery(fb, 1, 2, s->battery, s->charging);

    if (central) {
        /* Output: "USB" or "BT1".."BT5". Filled box = connected. */
        char label[4] = "USB";
        if (!s->usb) {
            label[0] = 'B';
            label[1] = 'T';
            label[2] = (char)('1' + (s->profile < 0 ? 0 : s->profile % 9));
        }
        int w = text_width(label, 1) + 4;
        int x = NVC_W - w;
        rect(fb, x, 1, w, 11, s->connected);
        text(fb, x + 2, 3, label, 1, !s->connected);
    } else {
        /* Link to the left half: filled dot = connected, ring = not connected. */
        int cx = NVC_W - 6, cy = 6;
        for (int dy = -4; dy <= 4; dy++) {
            for (int dx = -4; dx <= 4; dx++) {
                int d = dx * dx + dy * dy;
                if (d <= 17 && (s->connected || d >= 9)) {
                    px(fb, cx + dx, cy + dy, true);
                }
            }
        }
    }
}

/* ---------- layer list (left half) ---------- */

void nvc_draw_layers(nvc_fb_t fb, const char *const names[], int count, int active) {
    for (int x = 0; x < NVC_W; x++) {
        px(fb, x, 15, true);
    }
    if (count > NVC_MAX_LAYERS) {
        count = NVC_MAX_LAYERS;
    }
    for (int i = 0; i < count; i++) {
        int y = 21 + i * 23;
        char name[5] = {0};
        if (names[i] != NULL && names[i][0] != '\0') {
            strncpy(name, names[i], 4);
        } else {
            name[0] = (char)('0' + i);
        }
        if (i == active) {
            rect(fb, 1, y, 12, 16, true);
        }
        text(fb, 17, y + 1, name, 2, true);
    }
}

/* ---------- scene (right half) ---------- */

/* Mountain ridge, left to right: a smaller peak on the left, the main peak
 * right of centre. Everything below the ridge is mountain. */
static const uint8_t ridge_pts[][2] = {
    {0, 134}, {7, 125}, {13, 119}, {18, 125}, {23, 121}, {29, 113}, {40, 99},
    {46, 108}, {50, 105}, {57, 115}, {63, 121}, {67, 126},
};
#define RIDGE_N ((int)(sizeof(ridge_pts) / sizeof(ridge_pts[0])))

static uint8_t ridge[NVC_W];
static bool ridge_ready;

static void build_ridge(void) {
    for (int i = 0; i + 1 < RIDGE_N; i++) {
        int x0 = ridge_pts[i][0], y0 = ridge_pts[i][1];
        int x1 = ridge_pts[i + 1][0], y1 = ridge_pts[i + 1][1];
        for (int x = x0; x <= x1; x++) {
            ridge[x] = (uint8_t)(y0 + (y1 - y0) * (x - x0) / (x1 - x0));
        }
    }
    ridge_ready = true;
}

/* Cumulus clouds: overlapping circles with a flat base. Offsets from the
 * cloud's top left corner. */
struct puff {
    int8_t x, y, r;
};
struct cloud_shape {
    const struct puff *puffs;
    uint8_t n, w, base;
};

static const struct puff big_p[] = {{7, 11, 6}, {15, 7, 8}, {24, 6, 7}, {31, 10, 6}, {37, 13, 4}};
static const struct puff mid_p[] = {{6, 8, 5}, {13, 5, 6}, {20, 7, 5}, {25, 10, 3}};
static const struct puff small_p[] = {{4, 5, 4}, {10, 4, 5}, {15, 6, 3}};
static const struct cloud_shape BIG = {big_p, 5, 42, 17};
static const struct cloud_shape MID = {mid_p, 4, 29, 13};
static const struct cloud_shape SMALL = {small_p, 3, 19, 9};

struct cloud {
    const struct cloud_shape *shape;
    int16_t y;      /* top edge */
    int16_t speed;  /* sixteenths of a pixel per frame at normal speed */
    int32_t x16;    /* left edge in sixteenths of a pixel */
};

/* Back to front: higher clouds are farther away, smaller and slower. The
 * lowest ones pass behind the mountain. */
static struct cloud clouds[] = {
    {&SMALL, 18, 2, 10 * 16}, {&MID, 30, 3, 44 * 16},  {&SMALL, 46, 3, -6 * 16},
    {&BIG, 56, 4, 30 * 16},   {&MID, 76, 5, -20 * 16}, {&SMALL, 88, 5, 50 * 16},
    {&BIG, 96, 6, 8 * 16},
};
#define CLOUD_N ((int)(sizeof(clouds) / sizeof(clouds[0])))

static uint32_t rng = 0x2545F491u;
static uint32_t next_rand(void) {
    rng ^= rng << 13;
    rng ^= rng >> 17;
    rng ^= rng << 5;
    return rng;
}

void nvc_scene_step(int speed16) {
    for (int i = 0; i < CLOUD_N; i++) {
        struct cloud *c = &clouds[i];
        c->x16 -= (c->speed * speed16) / 16;
        if (c->x16 / 16 < -(int)c->shape->w) {
            /* Re-enter from the right after a random gap. */
            c->x16 = (NVC_W + (int)(next_rand() % 24)) * 16;
        }
    }
}

static bool in_cloud(const struct cloud *c, int x, int y) {
    int lx = x - c->x16 / 16, ly = y - c->y;
    const struct cloud_shape *s = c->shape;
    if (lx < 0 || lx >= s->w || ly < 0 || ly > s->base) {
        return false;
    }
    for (int i = 0; i < s->n; i++) {
        int dx = lx - s->puffs[i].x, dy = ly - s->puffs[i].y;
        if (dx * dx + dy * dy <= s->puffs[i].r * s->puffs[i].r) {
            return true;
        }
    }
    return false;
}

/* Ink for a sky pixel: the outline of the front-most cloud covering it. */
static bool sky_px(int x, int y) {
    for (int i = CLOUD_N - 1; i >= 0; i--) {
        const struct cloud *c = &clouds[i];
        if (in_cloud(c, x, y)) {
            return !in_cloud(c, x - 1, y) || !in_cloud(c, x + 1, y) || !in_cloud(c, x, y - 1) ||
                   !in_cloud(c, x, y + 1);
        }
    }
    return false;
}

static bool mountain_px(int x, int y) {
    int r = ridge[x];
    if (y == NVC_H - 1) {
        return true; /* ground */
    }
    int rl = ridge[x > 0 ? x - 1 : x], rr = ridge[x < NVC_W - 1 ? x + 1 : x];
    if (y <= r + 1 || y < rl || y < rr) {
        return true; /* ridge line, 2 px */
    }
    /* Snow on the main peak (ragged lower edge) and a dusting on the small one. */
    if (x >= 31 && x <= 50 && y <= 108 + ((x * 7) % 3)) {
        return true;
    }
    if (x >= 10 && x <= 16 && y <= 122) {
        return true;
    }
    /* Faces that slope down to the right are in shadow: denser shading. */
    bool shadow = rr > r;
    if (shadow) {
        return ((x + y) % 3 == 0);
    }
    return (y % 3 == 0) && ((x + y) % 6 == 0);
}

void nvc_draw_scene(nvc_fb_t fb) {
    if (!ridge_ready) {
        build_ridge();
    }
    for (int y = 16; y < NVC_H; y++) {
        for (int x = 0; x < NVC_W; x++) {
            bool on = (y >= ridge[x]) ? mountain_px(x, y) : sky_px(x, y);
            if (on) {
                fb[y][x] = 1;
            }
        }
    }
}
