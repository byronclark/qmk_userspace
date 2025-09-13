#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
#if defined(RGB_MATRIX_ENABLE)
    rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
    rgb_matrix_sethsv_noeeprom(RGB_MATRIX_DEFAULT_HUE,
                               RGB_MATRIX_DEFAULT_SAT,
                               RGB_MATRIX_DEFAULT_VAL);
#endif
}
