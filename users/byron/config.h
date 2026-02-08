#pragma once

#define TAPPING_TERM 250
#define PERMISSIVE_HOLD             // Hold on nested taps (ZMK "balanced")
#define FLOW_TAP_TERM 100           // Fast-typing bypass (ZMK require-prior-idle)
#define CHORDAL_HOLD                // Opposite-hands rule (replaces Achordion)
#define SPECULATIVE_HOLD            // Immediate modifier (ZMK hold-while-undecided)

#define CAPS_WORD_IDLE_TIMEOUT 5000

// RGB matrix (ErgoDox EZ, Kyria)
#if defined(RGB_MATRIX_ENABLE)
#define RGB_MATRIX_KEYRELEASES
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_SPLASH
#define RGB_MATRIX_DEFAULT_HUE 191
#define RGB_MATRIX_DEFAULT_SAT 255
#define RGB_MATRIX_DEFAULT_VAL 150
#endif

// Disable ErgoDox Oryx features
#undef ORYX_CONFIGURATOR
#undef ORYX_ENABLE
