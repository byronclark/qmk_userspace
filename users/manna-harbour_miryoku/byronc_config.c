#include QMK_KEYBOARD_H
#include "features/achordion.h"

void keyboard_post_init_user(void) {
#if defined(RGB_MATRIX_ENABLE)
    rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
    rgb_matrix_sethsv_noeeprom(RGB_MATRIX_DEFAULT_HUE,
                               RGB_MATRIX_DEFAULT_SAT,
                               RGB_MATRIX_DEFAULT_VAL);
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_achordion(keycode, record)) { return false; }

    return true;
}

void matrix_scan_user(void) {
    achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {

    /* Consider these same hand chords as holds. This is specific to Miryoku Colemak. */
    switch (tap_hold_keycode) {
    case LGUI_T(KC_O):
        if (other_keycode == KC_K) { return true; } /* macOS Slack everything key */
        break;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

bool achordion_eager_mod(uint8_t mod) {
    switch (mod) {
    case MOD_LSFT:
    case MOD_LCTL:
    case MOD_LALT:
        return true;            /* Eagerly apply ctrl, alt, and shift */

    default:
        return false;
    }
}
