// ErgoDox EZ: 14 rows x 6 cols
// Rows 0-6 = left half, rows 7-13 = right half
#include QMK_KEYBOARD_H

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_ergodox_pretty(
        'L', 'L', 'L', 'L', 'L', 'L', 'L',     'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L',     'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',                'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L',     'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',                          'R', 'R', 'R', 'R', 'R',
                             '*', '*',     '*', '*',
                                  '*',     '*',
                        '*', '*', '*',     '*', '*', '*'
    );
