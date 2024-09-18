/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum _layers {
    _QWERTY = 0,
    _MEDIA,
    _NAV,
    _MOUSE,
    _SYM,
    _NUM,
    _FUN,
};

// clang-format off

// Declare a variable to track if the accent mode is enabled
bool accent_mode = false;
enum custom_keycodes {
    KC_BSPC_DEL = SAFE_RANGE,
    A_ACCENT,
    N_TILDE,
    ACCENT_KEY,
};

#include "tapdance.c"

#define M_LGUI OSM(MOD_LGUI)
#define M_LALT OSM(MOD_LALT)
#define M_LCTL OSM(MOD_LCTL)
#define M_LSFT OSM(MOD_LSFT)

#define M_RGUI OSM(MOD_RGUI)
#define M_RALT OSM(MOD_RALT)
#define M_RCTL OSM(MOD_RCTL)
#define M_RSFT OSM(MOD_RSFT)

#define L_MEDIA LT(_MEDIA, KC_ENT)
#define L_NAV LT(_NAV, KC_TAB)
#define M_ESC_SHFT MT(MOD_LSFT, KC_ESC)
#define L_SYM_ENT LT(_SYM, KC_ENT)
#define L_SYM_SPC LT(_SYM, KC_SPC)
#define L_NUM LT(_NUM, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | GRV  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |KC_BSPC|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  | A    | S    | D    | F    |   G  |                    |   H  | J    | K    | L    |  SCLN|  Ñ   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |KC_ENT|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          |Ent   | Tab  | /Esc    /       \Space \  |Backsp|     |
 *                          |_MEDIA| _NAV |/SHIFT /         \ _SYM \ |_NUM  |_FUN |
 *                          `--------------------'           '------''-------------'
 */

[_QWERTY] = LAYOUT(
  TD(TD_GRV),   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,  KC_P,    KC_BSPC,
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,  TD(TD_SCLN), TD(TD_SP),
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,              KC_N,    KC_M,    TD(TD_COMM),  TD(TD_DOT),  TD(TD_SLSH), KC_RSFT,
                                L_MEDIA, L_NAV, M_ESC_SHFT,      L_SYM_SPC, L_NUM, OSL(_FUN)
),

/* NAV
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |       |     |      |      |                    | Home | Down | Up   | End  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Shift| Ctrl | Opt  | Cmd  |      |                    |  Left | Down | Up  | Right|      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          |Ent   | Tab  | /  Esc  /       \Enter \  |Backsp|       |
 *                          |_MEDIA| _NAV |/SHIFT /         \ _SYM \ |_NUM  | _FUN  |
 *                          `--------------------'           '------''--------------'
 */
[_NAV] = LAYOUT(
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           KC_HOME, KC_PGDN, KC_PGUP, KC_END,   _______, _______,
  _______, M_LSFT,  M_LCTL, M_LALT,  M_LGUI,  XXXXXXX,            KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX, KC_QUOTE,
  _______, KC_UNDO, KC_CUT,KC_COPY, KC_PASTE, XXXXXXX,            XXXXXXX, KC_PASTE,KC_COPY, KC_CUT,   KC_UNDO, KC_ENT,
                              _______, _______, _______,      L_SYM_ENT, _______, _______

    ),
/* SYM
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  [   |  &   |  *   |  (   |  }   |                    | PWrd | NWrd | Pscr |Scroll| Pause| F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  :   |  $   |  %   |  ^   |  +   |                    |      | Cmd | Opt  | Ctrl  | Shift|      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |     |      |       |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          |Ent   | Tab  | /Esc    /       \Space \  |Backsp|     |
 *                          |_MEDIA| _NAV |/SHIFT /         \ _SYM \ |_NUM  |_FUN |
 *                          `--------------------'           '------''--------------'
 */
[_SYM] = LAYOUT(
  XXXXXXX,KC_LCBR, KC_AMPR,KC_ASTR,KC_LPRN, KC_RCBR,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX,KC_SCLN, KC_DLR, KC_PERC,KC_CIRC, KC_PLUS,              XXXXXXX, M_RGUI , M_RALT,  M_RCTL,  M_RSFT,  _______,
  XXXXXXX,KC_TILD, KC_EXLM,KC_AT,  KC_HASH, KC_PIPE,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,
                                KC_LPRN, KC_RPRN, KC_UNDS,    _______, _______, _______
),

/* NUM
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  [   |  7   |  8   |  9   |  ]   |     |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ;   |  4   |  5   |  6   |  =   |      |                    |      | Cmd | Opt  | Ctrl  | Shift|      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |  1   |  2   |  3   |  \   |      |-------|    |-------|      | Menu |  Del |  End | PDown|      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          |  .   |  0   | /Esc    /       \Space \  |Backsp|     |
 *                          |      |      |/SHIFT /         \ _SYM \ |_NUM  |_FUN |
 *                          `--------------------'           '------''--------------'
 */
[_NUM] = LAYOUT(
  KC_LBRC, _______, KC_7, KC_8,  KC_9,  KC_RBRC,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______,_______,  KC_4, KC_5,  KC_6,  KC_EQL ,                  XXXXXXX, M_RGUI , M_RALT,  M_RCTL,  M_RSFT,  _______,
  _______,_______,  KC_1, KC_2,  KC_3,  KC_BSLS,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,
                               KC_DOT, KC_0, KC_MINUS,        _______, _______, _______
),

/* FUN
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |  Up  |      |QK_BOOT|     |                    | PWrd | NWrd | Pscr |Scroll| Pause| F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps | Left | Down | Rigth|      |      |                    |  Ins | Home | PUp  |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |-------|    |-------|      | Menu |  Del |  End | PDown|      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          |Ent   | Tab  | /Esc    /       \Space \  |Backsp|     |
 *                          |_MEDIA| _NAV |/SHIFT /         \ _SYM \ |_NUM  |_FUN |
 *                          `--------------------'           '------''--------------'
 */
[_FUN] = LAYOUT(
  KC_ESC,  KC_ESC, KC_F7, KC_F8,  KC_F9, XXXXXXX,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  _______, _______,KC_F4, KC_F5,  KC_F6, XXXXXXX,                 XXXXXXX, M_RGUI , M_RALT,  M_RCTL,  M_RSFT,  KC_ENT,
  _______, _______,KC_F1, KC_F2,  KC_F3, XXXXXXX,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,
                                _______, _______, _______,    _______, _______, _______
),

/* MEDIA
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |  Up  |      |QK_BOOT|     |                    |TOGGLE| HUD  |  HUI | MOD  |Scroll| Pause|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps | Left | Down | Rigth|      |      |                    |  Ins | Home | PUp  |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |-------|    |-------|      | Menu |  Del |  End | PDown|      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          |Ent   | Tab  | /Esc    /       \Space \  |Backsp|     |
 *                          |_MEDIA| _NAV |/SHIFT /         \ _SYM \ |_NUM  |_FUN |
 *                          `--------------------'           '------''--------------'
 */
[_MEDIA] = LAYOUT(
  _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          RGB_TOG, RGB_HUD, RGB_HUI, RGB_MOD, RGB_SAI, RGB_SAD,
  _______,  M_LSFT,  M_LCTL, M_LALT,   M_LGUI,  XXXXXXX,          XXXXXXX, M_RGUI , M_RALT,  M_RCTL,  M_RSFT,KC_ENT,
  _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,
                                _______, _______, _______,    _______, _______, _______
),

/* MOUSE
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |  Up  |      |QK_BOOT|     |                    | PWrd | NWrd | Pscr |Scroll| Pause| F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps | Left | Down | Rigth|      |      |                    |  Ins | Home | PUp  |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |-------|    |-------|      | Menu |  Del |  End | PDown|      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          |Ent   | Tab  | /Esc    /       \Space \  |Backsp|     |
 *                          |_MEDIA| _NAV |/SHIFT /         \ _SYM \ |_NUM  |_FUN |
 *                          `--------------------'           '------''--------------'
 */
[_MOUSE] = LAYOUT(
  KC_ESC,  KC_INS,  KC_AMPR,  KC_ASTR,  KC_LPRN, KC_RPRN,         KC_PGUP, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
  _______,  KC_LALT, KC_DLR,  KC_PERC,  KC_CIRC, KC_CAPS,         KC_PGDN, KC_4,  KC_5, KC_6,KC_DEL,   KC_ENT,
  _______,  KC_UNDO, KC_EXLM,   KC_AT, KC_HASH, XXXXXXX,          XXXXXXX, KC_1, KC_2, KC_3, _______, _______,
                                _______, _______, _______,    _______, _______, _______
),

};
// clang-format on

/* 32 * 32 logo */
static void render_logo(void) {
    static const char PROGMEM hell_logo[] = {0x00, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x1c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x78, 0x1e, 0x06, 0x00, 0x0c, 0x1c, 0x18, 0x30, 0x30, 0x60, 0x60, 0xc0, 0xc0, 0x80, 0x00, 0x01, 0x03, 0x07, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x70, 0x60, 0x00, 0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x60, 0x70, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x07, 0x03, 0x01, 0x00, 0xf8, 0xf8, 0x80, 0x80, 0x80, 0xf8, 0xf8, 0x00, 0x80, 0xc0, 0xc0, 0x40, 0xc0, 0xc0, 0x80, 0x00, 0xf8, 0xf8, 0x00, 0xf8, 0xf8, 0x00, 0x08, 0x38, 0x08, 0x00, 0x38, 0x08, 0x30, 0x08, 0x38, 0x00, 0x1f, 0x1f, 0x01, 0x01, 0x01, 0x1f, 0x1f, 0x00, 0x0f, 0x1f, 0x1a, 0x12, 0x1a, 0x1b, 0x0b, 0x00, 0x1f, 0x1f, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    oled_write_raw_P(hell_logo, sizeof(hell_logo));
}

/* 32 * 14 os logos */
static const char PROGMEM mac_logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf0, 0xf6, 0xfb, 0xfb, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* Smart Backspace Delete */

bool            shift_held = false;
static uint16_t held_shift = 0;

/* KEYBOARD PET START */

/* settings */
#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40

/* advanced settings */
#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE 96            // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;
led_t led_usb_state;

bool isSneaking = false;
bool isJumping  = false;
bool showedJump = true;

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'sit2', 32x22px */
                                                   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'walk2', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'run2', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   }};

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
                                                    {
                                                        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'bark2', 32x22px */
                                                    {
                                                        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
                                                     },

                                                     /* 'sneak2', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                     }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y - 1);

            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y);
        }

        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if (led_usb_state.caps_lock) {
            oled_write_raw_P(bark[current_frame], ANIM_SIZE);

        } else if (isSneaking) {
            oled_write_raw_P(sneak[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[current_frame], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[current_frame], ANIM_SIZE);
        }
    }

#if OLED_TIMEOUT > 0
    /* the animation prevents the normal timeout from occuring */
    if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }
#endif

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}

/* KEYBOARD PET END */

static void print_logo_narrow(void) {
    render_logo();

    /* wpm counter */
    uint8_t n = get_current_wpm();
    char    wpm_str[4];
    oled_set_cursor(0, 14);
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + n % 10;
    wpm_str[1] = '0' + (n /= 10) % 10;
    wpm_str[0] = '0' + n / 10;
    oled_write(wpm_str, false);

    oled_set_cursor(0, 15);
    oled_write(" wpm", false);
}

static void print_status_narrow(void) {
    /* Print current mode */
    oled_set_cursor(0, 0);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_raw_P(mac_logo, sizeof(mac_logo));
    } else {
        oled_write_raw_P(mac_logo, sizeof(mac_logo));
    }

    oled_set_cursor(0, 3);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write("QWRTY", false);
            break;
        case _MEDIA:
            oled_write("Media", false);
            break;
        case _NAV:
            oled_write("Nav  ", false);
            break;
        case _MOUSE:
            oled_write("Mouse", false);
            break;
        case _SYM:
            oled_write("Sym  ", false);
            break;
        case _NUM:
            oled_write("Num  ", false);
            break;
        case _FUN:
            oled_write("Fun  ", false);
            break;
        default:
            oled_write("UNDEF", false);
    }

    oled_set_cursor(0, 5);

    /* Print current layer */
    oled_write("LAYER", false);

    oled_set_cursor(0, 6);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write("QWRTY", false);
            break;
        case _MEDIA:
            oled_write("Media", false);
            break;
        case _NAV:
            oled_write("Nav  ", false);
            break;
        case _MOUSE:
            oled_write("Mouse", false);
            break;
        case _SYM:
            oled_write("Sym  ", false);
            break;
        case _NUM:
            oled_write("Num  ", false);
            break;
        case _FUN:
            oled_write("Fun  ", false);
            break;
    }

    /* caps lock */
    oled_set_cursor(0, 8);
    oled_write("CPSLK", led_usb_state.caps_lock);

    /* KEYBOARD PET RENDER START */

    render_luna(0, 13);

    /* KEYBOARD PET RENDER END */
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    /* KEYBOARD PET VARIABLES START */

    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    /* KEYBOARD PET VARIABLES END */

    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LGUI));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LGUI));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LGUI));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LGUI));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LGUI));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LGUI));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LGUI));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LGUI));
                unregister_code(KC_Z);
            }
            return false;

            /* Smart Backspace Delete */

        case KC_RSFT:
        case KC_LSFT:
            shift_held = record->event.pressed;
            held_shift = keycode;
            break;
        case KC_BSPC_DEL:
            if (record->event.pressed) {
                if (shift_held) {
                    unregister_code(held_shift);
                    register_code(KC_DEL);
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                unregister_code(KC_DEL);
                unregister_code(KC_BSPC);
                if (shift_held) {
                    register_code(held_shift);
                }
            }
            return false;

            /* KEYBOARD PET STATUS START */

        case MOD_RGUI:
        case MOD_LGUI:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case L_SYM_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;

            /* KEYBOARD PET STATUS END */
    }
    return true;
}
