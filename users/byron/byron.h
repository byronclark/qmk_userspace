#pragma once

#include QMK_KEYBOARD_H

enum byron_layers {
    _BASE,
    _NAV,
    _NUM,
    _SYM,
    _FUN,
    _MEDIA,
    _MOUSE,
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
#define NUM_BSP LT(_NUM, KC_BSPC)
#define SYM_ENT LT(_SYM, KC_ENT)
#define FUN_DEL LT(_FUN, KC_DEL)
#define MED_ESC LT(_MEDIA, KC_ESC)
#define MSE_TAB LT(_MOUSE, KC_TAB)
