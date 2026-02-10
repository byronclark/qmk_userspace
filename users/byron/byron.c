#include "byron.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_byron(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,        KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        HM_A,    HM_R,    HM_S,    HM_T,    KC_D,        KC_H,    HM_N,    HM_E,    HM_I,    HM_O,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        XXXXXXX, XXXXXXX, MED_ESC, NAV_SPC, MSE_TAB,     SYM_ENT, NUM_BSP, FUN_DEL, XXXXXXX, XXXXXXX
    ),

    [_NAV] = LAYOUT_byron(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,     CW_TOGG, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,
        XXXXXXX, XXXXXXX, _______, _______, _______,      KC_ENT, KC_BSPC, KC_DEL,  XXXXXXX, XXXXXXX
    ),

    [_NUM] = LAYOUT_byron(
        KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,      XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_DOT,  KC_0,    KC_MINS,     _______, _______, _______, XXXXXXX, XXXXXXX
    ),

    [_SYM] = LAYOUT_byron(
        KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,     XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, KC_UNDS,     _______, _______, _______, XXXXXXX, XXXXXXX
    ),

    [_FUN] = LAYOUT_byron(
        KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,    XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI,
        KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, _______, _______, _______,    _______, _______, _______, XXXXXXX, XXXXXXX
    ),

    [_MEDIA] = LAYOUT_byron(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, _______, _______, _______,    KC_MSTP, KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX
    ),

    [_MOUSE] = LAYOUT_byron(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR,
        XXXXXXX, XXXXXXX, _______, _______, _______,    MS_BTN2, MS_BTN1, MS_BTN3, XXXXXXX, XXXXXXX
    ),
};
// clang-format on

#ifdef FLOW_TAP_TERM_PER_KEY
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t* record, uint16_t prev_keycode) {
    switch (keycode) {
        case HM_A:  // Left pinky GUI
        case HM_O:  // Right pinky GUI
            return FLOW_TAP_TERM;
        default:
            return 0;  // Disable Flow Tap for all other mod-taps
    }
}
#endif

#ifdef QUICK_TAP_TERM_PER_KEY
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // All thumb layer-tap keys get tight 80ms window
        case NAV_SPC:   // LT(_NAV, KC_SPC)
        case NUM_BSP:   // LT(_NUM, KC_BSPC)
        case SYM_ENT:   // LT(_SYM, KC_ENT)
        case FUN_DEL:   // LT(_FUN, KC_DEL)
        case MED_ESC:   // LT(_MEDIA, KC_ESC)
        case MSE_TAB:   // LT(_MOUSE, KC_TAB)
            return 80;  // Tight window - requires intentional double-tap
        default:
            return QUICK_TAP_TERM;  // Normal timing for all other keys
    }
}
#endif

#ifdef CHORDAL_HOLD
// Allow same-hand copy/paste and browser devtools
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
                      uint16_t other_keycode, keyrecord_t *other_record) {
    switch (tap_hold_keycode) {
        // Left hand: Ctrl/Cmd + C/X/V for copy/paste
        case HM_S:
        case HM_A:
            switch (other_keycode) {
                case KC_C:
                case KC_X:
                case KC_V:
                    return true;
            }
            break;

        // Right hand: Cmd/Opt + K/J for browser devtools
        case HM_O:  // Right Cmd
        case HM_I:  // Right Opt
            switch (other_keycode) {
                case KC_K:  // Firefox Cmd+Opt+K
                case KC_J:  // Chrome Cmd+Opt+J
                    return true;
            }
            break;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}
#endif
