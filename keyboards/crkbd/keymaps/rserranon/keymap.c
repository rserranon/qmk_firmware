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
#include <stdio.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// clang-format off


// Each layer gets a name for readability.
enum layer_names {
    _BASE,
    _NUM,
    _SYM,
    _ADJ,
};

// Home Rows

// Left-hand home row mods
#define SFT_A LSFT_T(KC_A)
#define CTL_S LCTL_T(KC_S)
#define ALT_D LALT_T(KC_D)
#define GUI_F LGUI_T(KC_F)

// Right-hand home row mods
#define GUI_J RGUI_T(KC_J)
#define ALT_K LALT_T(KC_K)
#define CTL_L RCTL_T(KC_L)
#define SFT_SCLN RSFT_T(KC_SCLN)

// Define tap dance keycodes
enum {
    TD_ESC = 0, // Tap dance identifier for Esc/`
    TD_SCLN, // Tap dance identifier for ;/:
    TD_COMM,      // Tap dance identifier for ,/<
    TD_DOT,        // Tap dance identifier for ./>
    TD_SLSH,      // Tap dance identifier for /?
};

// Tap Dance definitions

void dance_scln_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_RSFT);
        tap_code(KC_SCLN);
        unregister_code(KC_RSFT);
    } else if (state->count == 2) {
        tap_code16(S(KC_SCLN));  // Send colon `:`
    }
}

void dance_scln_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_RSFT);
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
    [TD_SCLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_scln_finished, dance_scln_reset),
    [TD_COMM] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_LABK),
    [TD_DOT] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_RABK),
    [TD_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
};

enum custom_keycodes {
  ACCENT = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TAB,   SFT_A,   CTL_S,   ALT_D,   GUI_F,   KC_G,                         KC_H,   GUI_J,   ALT_K,   CTL_L, TD_SCLN,  ACCENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_GRV,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, TD_COMM,  TD_DOT, TD_SLSH,  KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_GRV, LT(1, KC_ESC),KC_ENT,   KC_SPC ,LT(2, KC_BSPC), MO(3)
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO, KC_PSCR,    KC_7,    KC_8,    KC_9,    KC_0,                      KC_HOME, KC_PGUP, KC_PGDN,  KC_END,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,    KC_4,    KC_5,    KC_6,    KC_0,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,    KC_1,    KC_2,    KC_3,    KC_0,                        KC_NO,   KC_NO, KC_PCMM, KC_PDOT,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_NO, LT(1, KC_ESC),KC_ENT,   KC_SPC ,LT(2, KC_BSPC), KC_NO
                                      //`--------------------------'  `--------------------------'
    ),

  [_SYM] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO, KC_PIPE,  KC_NO, KC_NO   , KC_LPRN, KC_LCBR,                      KC_RCBR, KC_RPRN, KC_QUES, KC_PEQL, KC_PLUS, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO, KC_BSLS,   KC_NO,   KC_NO,   KC_LT, KC_LBRC,                      KC_RBRC,   KC_GT, KC_TILD,  KC_GRV, KC_CIRC,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_NO, LT(1, KC_ESC),KC_ENT,   KC_SPC ,LT(2, KC_BSPC), KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJ] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,   QK_BOOT,   KC_F7,   KC_F8, KC_F9,  KC_F10,                      KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MSTP,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO, KC_CAPS,   KC_F4,   KC_F5,   KC_F6,  KC_F11,                      KC_BTN4, KC_WH_D, KC_WH_U, KC_BTN5,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO, KC_PSCR,   KC_F1,   KC_F2,   KC_F3,  KC_F12,                      KC_BTN2, KC_WH_L, KC_WH_R, KC_BTN3,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_NO, LT(1, KC_ESC),KC_ENT,   KC_SPC ,LT(2, KC_BSPC), KC_NO
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case _BASE:
            oled_write_ln_P(PSTR("Qwerty\n"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("NumNav\n"), false);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("Symbols\n"), false);
            break;
        case _ADJ:
            oled_write_ln_P(PSTR("FMouse\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Default\n"), false);
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
        return true;
    } else {
        oled_render_logo();
        return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ACCENT:
            if (record->event.pressed) {
                // Send Option + E
                register_code(KC_LALT); // Press Option (Alt) key
                tap_code(KC_E);         // Tap E key
                unregister_code(KC_LALT); // Release Option (Alt) key
            }
            return false; // Return false to stop other key processing
        default:
            return true; // Process all other keycodes normally
    }
}
#endif // OLED_ENABLE
