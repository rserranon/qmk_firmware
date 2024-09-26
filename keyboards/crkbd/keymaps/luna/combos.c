const uint16_t PROGMEM test_combo1[] = {KC_J, KC_K, COMBO_END};
combo_t                key_combos[]  = {
    COMBO(test_combo1, RGUI(KC_SPC)), // keycodes with modifiers are possible too!
};
