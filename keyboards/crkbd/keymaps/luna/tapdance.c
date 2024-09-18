#include QMK_KEYBOARD_H

// clang-format off

tap_dance_action_t *action;

// Tap Dance declarations
enum {
    TD_SCLN,
    TD_COMM,
    TD_DOT,
    TD_SLSH,
    TD_GRV,
    TD_SP,
};

// Tap Dance definitions
void tap_dance_sp_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Simulate Alt + E for accented vowels
        register_code(KC_LALT);
        tap_code(KC_E);
        unregister_code(KC_LALT);
    } else if (state->count == 2) {
        // Simulate Alt + N for ñ
        register_code(KC_LALT);
        tap_code(KC_N);
        unregister_code(KC_LALT);
    }
}

void tap_dance_sp_reset(tap_dance_state_t *state, void *user_data) {
    // Reset logic (if needed)
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_SCLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_COMM] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_LT),
    [TD_DOT]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_GT),
    [TD_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
    [TD_GRV]  = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD),
    [TD_SP]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_sp_finished, tap_dance_sp_reset),
};
