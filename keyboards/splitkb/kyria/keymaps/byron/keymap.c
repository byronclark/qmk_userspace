// Kyria rev3: 8 rows x 7 cols (split)
// Rows 0-3 = left half, rows 4-7 = right half
#include QMK_KEYBOARD_H

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',                          'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',                          'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', '*', '*',    '*', '*',   'R', 'R', 'R', 'R', 'R', 'R',
                   '*', '*', '*', '*', '*',    '*', '*', '*', '*', '*'
    );
