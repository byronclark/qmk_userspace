# QMK Userspace

QMK external userspace for Byron's keyboards. Lives alongside the QMK firmware repo at `~/sandbox/current/qmk_firmware`.

## Keyboards

| Keyboard | Compile command |
|----------|----------------|
| Atreus | `qmk compile -kb keyboardio/atreus -km byron` |
| Kyria rev3 | `qmk compile -e CONVERT_TO=rp2040_ce -e RGB_MATRIX_ENABLE=no -e OLED_ENABLE=no -kb splitkb/kyria/rev3 -km byron` |
| ErgoDox EZ Glow | `qmk compile -kb ergodox_ez/glow -km byron` |

The Kyria uses an rp2040_ce microcontroller and has no RGB or OLED hardware. Its adapter also sets `DEBOUNCE 15` + `DEBOUNCE_TYPE = sym_eager_pk` to absorb intermittent contact chatter that produces double letters (e.g. on `y`). See TUNING.md.

## Architecture

36-key canonical layout with per-keyboard adapters, same pattern as Miryoku.

### Shared code (`users/byron/`)
- `byron.h` — Layer enums, homerow mod aliases (`HM_A` etc), thumb key aliases (`NAV_SPC`, `NUM_BSP` etc)
- `byron.c` — All 7 layers defined here using `LAYOUT_byron()`. Included via `INTROSPECTION_KEYMAP_C` (not `SRC +=`) because QMK's `keymap_introspection.c` needs `sizeof(keymaps)` at compile time
- `config.h` — Timeless homerow mod settings (CHORDAL_HOLD, PERMISSIVE_HOLD_PER_KEY), RGB defaults, Oryx disable
- `rules.mk` — Feature flags and `INTROSPECTION_KEYMAP_C = byron.c`
- `TUNING.md` — Timing tuning guide; update when changing timing constants or per-key overrides

### Per-keyboard adapters (`keyboards/.../keymaps/byron/`)
Each has:
- `config.h` — Defines `LAYOUT_byron()` macro mapping 36 keys to the keyboard's native LAYOUT
- `keymap.c` — Defines `chordal_hold_layout` using the keyboard's native LAYOUT macro (L/R/\* for left/right/thumb)

### Adapter locations
- Atreus: `keyboards/keyboardio/atreus/keymaps/byron/`
- Kyria: `keyboards/splitkb/kyria/keymaps/byron/`
- ErgoDox: `keyboards/ergodox_ez/keymaps/byron/`

## Layers

| Layer | Activation | Content |
|-------|-----------|---------|
| BASE | default | Colemak + homerow mods (GUI/ALT/CTL/SFT) |
| NAV | hold Space | Arrows, Home/End, PgUp/PgDn, Caps Word |
| NUM | hold Bspc | Number pad + arithmetic operators |
| SYM | hold Enter | Shifted symbols + brackets |
| FUN | hold Del | F-keys |
| MEDIA | hold Esc | Media transport (prev/next, vol, play/stop/mute) |
| MOUSE | hold Tab | Mouse movement, scroll wheel, buttons |

## Key design decisions
- Uses LALT (not RALT/AltGr) on both hands for homerow mods
- Non-base layers have plain mods on the opposite hand (e.g. NAV has arrow keys right, plain GUI/ALT/CTL/SFT left)
- PERMISSIVE_HOLD disabled for GUI keys (HM_A, HM_O) and LALT keys (HM_R, HM_I) — bigrams like `space a space`, `space o` were triggering CMD+Space, and `it`, `re` were triggering Option on macOS; Ctrl/Shift keep permissive hold
- Miryoku keymaps (`-km manna-harbour_miryoku`) coexist untouched in this repo
