#pragma once

#include QMK_KEYBOARD_H

enum byron_layers {
    _BASE,
    _NAV,
    _NUM,
    _SYM,
    _FUN,
};

// Left hand homerow mods
#define HM_A LGUI_T(KC_A)
#define HM_R LALT_T(KC_R)
#define HM_S LCTL_T(KC_S)
#define HM_T LSFT_T(KC_T)

// Right hand homerow mods
#define HM_N RSFT_T(KC_N)
#define HM_E RCTL_T(KC_E)
#define HM_I LALT_T(KC_I)   // LALT not RALT to avoid AltGr
#define HM_O RGUI_T(KC_O)

// Thumb keys
#define NAV_SPC LT(_NAV, KC_SPC)
#define NUM_TAB LT(_NUM, KC_TAB)
#define SYM_BSP LT(_SYM, KC_BSPC)
#define FUN_DEL LT(_FUN, KC_DEL)
