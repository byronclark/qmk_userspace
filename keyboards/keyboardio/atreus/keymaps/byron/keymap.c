// Atreus: 4 rows x 12 cols
// Cols 0-4 = left, 5-6 = center, 7-11 = right
#include QMK_KEYBOARD_H

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L',              'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',              'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', '*',    '*', 'R', 'R', 'R', 'R', 'R',
        '*', '*', '*', '*', '*', '*',    '*', '*', '*', '*', '*', '*'
    );
