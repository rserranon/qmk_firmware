#include QMK_KEYBOARD_H

// Tap Dance declarations
enum {
    TD_SCLN,
    TD_COMM,
    TD_DOT,
    TD_SLSH,
    TD_GRV,
    TD_DQT,  // Re-added TD_DQT to the enum
    TD_SP,
};

// Tap Dance definitions
void tap_dance_sp_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Simulate Alt + E for accented vowels
        tap_code16(LALT(KC_E));
    } else if (state->count == 2) {
        // Simulate Alt + N for ñ
        tap_code16(LALT(KC_N));
    }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_SCLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_COMM] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_LT),
    [TD_DOT]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_GT),
    [TD_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
    [TD_GRV]  = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD),
    [TD_DQT]  = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQT),  // Re-added TD_DQT tap dance
    [TD_SP]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_sp_finished, NULL), // No reset function needed
};

