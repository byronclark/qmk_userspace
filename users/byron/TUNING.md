# Timing Tuning Guide

Reference for adjusting tap-hold timing constants. Each section describes what to look for and which direction to adjust.

## TAPPING_TERM (currently 200ms)

**Applies to:** All mod-tap and layer-tap keys.

**What it does:** The maximum time a key can be held before QMK commits to a hold. Below this window, a press-release is a tap; beyond it, it's a hold.

| Symptom | Direction | Example |
|---------|-----------|---------|
| Modifier combos register as taps (e.g. Ctrl+C types `sc`) | Decrease | Finish typing, quickly Ctrl+C in emacs |
| Normal typing triggers accidental holds/modifiers | Increase | Fast typing produces phantom Ctrl/GUI/Alt |

**History:** Was 250, bumped to 280 (mistake — made Ctrl worse), set to 200.

## PERMISSIVE_HOLD_PER_KEY

**Applies to:** All mod-taps, but only Ctrl/Shift keys return `true` from `get_permissive_hold()`. LGUI (HM_A), RGUI (HM_O), and LALT (HM_R, HM_I) keys return `false`.

**What it does:** When enabled for a key, a nested keypress (pressing another key while the mod-tap is held) immediately resolves the mod-tap as a hold, without waiting for TAPPING_TERM. When disabled for a key, a hold only fires after TAPPING_TERM expires.

| Symptom | Direction |
|---------|-----------|
| Common bigrams trigger Option on macOS (e.g. `it` → Option+T, `re` → Option+E) | Disable permissive hold for that LALT key |
| Fast typing triggers CMD+Space (e.g. `space a space`, `space o`) | Disable permissive hold for that GUI key |
| Intentional mod chord requires awkward deliberate hold | Re-enable permissive hold for that key (accepting the false trigger) |
| Ctrl/Shift fails to fire on fast nested keypresses | That key may have permissive hold inadvertently disabled |

**History:** Started with global `PERMISSIVE_HOLD`. Switched to `PERMISSIVE_HOLD_PER_KEY` and disabled for HM_R and HM_I after the `it` bigram (e.g. "sitting") was producing Option+T on macOS. Later disabled for HM_A and HM_O after `space a space` and `space o` sequences were triggering CMD+Space.

## QUICK_TAP_TERM (currently 80ms for thumb keys, 120ms for others)

**Applies to:** Thumb layer-tap keys (NAV_SPC, NUM_BSP, SYM_ENT, FUN_DEL, MED_ESC, MSE_TAB) via `get_quick_tap_term()`.

**What it does:** After tapping a key, if you press it again within this window, QMK registers a repeat tap instead of evaluating hold. Lower values require faster double-taps to repeat.

| Symptom | Direction | Example |
|---------|-----------|---------|
| Accidental repeated taps on thumb keys (double space, double backspace) | Decrease | Pressing space twice in quick succession when only one was intended |
| Can't intentionally repeat thumb keys fast enough | Increase | Want to tap-tap-tap space quickly but second tap activates layer |

**History:** Global default was 150, reduced to 120. Thumb keys use hardcoded 80ms; HM_E returns 0.

## Retired workarounds

- **Kyria `n`-switch chatter:** bumped `DEBOUNCE` to 15ms with `DEBOUNCE_TYPE = sym_eager_pk` in the Kyria adapter (commit `0924fac`), reverted once the hotswap socket was resoldered (`543e79a`). Reapplied when `y` started doubling (`67e48bf`), then dropped again to run on QMK defaults for a while. See those commits for the diagnostic details and the symptom-to-direction table; reapply if chatter returns.

## HOLD_ON_OTHER_KEY_PRESS_PER_KEY (currently disabled)

**Applies to:** Cross-thumb layer-tap keys (`NUM_BSP`, `SYM_ENT`, `FUN_DEL`, `MED_ESC`, `MSE_TAB`) via `get_hold_on_other_key_press()`, when `HOLD_ON_OTHER_KEY_PRESS_PER_KEY` is defined in `config.h` and the function is present in `byron.c`. `NAV_SPC` deliberately returned `false` (fell back to `PERMISSIVE_HOLD`) when this was active.

**What it does:** Permissive hold only commits a tap-hold key to *hold* if the interrupting key is pressed **and released** before the tap-hold key itself releases. Hold-on-other-key-press commits to hold the instant the other key is *pressed*, regardless of release order.

| Symptom | Direction | Example |
|---------|-----------|---------|
| A layer-tap key's own tap keycode fires (e.g. Backspace) instead of the layer activating, right when reaching a layer-shifted key on the *other* thumb | Enable hold-on-other-key-press for that key | Holding `NUM_BSP` for `-` (via `MSE_TAB`'s position) while typing `5-` or `d-`: releasing the right thumb (`NUM_BSP`) a beat before the left thumb (`MSE_TAB`) released `NUM_BSP` as a tap (Backspace) before the NUM layer ever activated, so the other key fell back to its base binding (`MSE_TAB` → Tab) instead of `-` |
| Fast prose typing starts triggering a non-base layer instead of that key's tap | Disable hold-on-other-key-press for that key | Rolling the next word's first letter into `NAV_SPC`'s release before actually releasing space would turn much normal typing into Nav-layer activations — this is why `NAV_SPC` is excluded |
| A layer-tap key's own tap keycode never fires at all, and the *other* thumb's ordinary rollover reads as a layer-shifted character instead | Disable hold-on-other-key-press for that key | With it enabled on `NUM_BSP`: an incidental left-thumb `NAV_SPC` press while `NUM_BSP` was still settling from an intended plain Backspace tap committed `NUM_BSP` to a hold immediately, so `NAV_SPC` read as the NUM layer's `KC_0` instead of Space, and the Backspace itself never fired since it only sends on tap resolution |

**History:** Diagnosed via `qmk console` (with `CONSOLE_ENABLE`/`ACTION_DEBUG` temporarily enabled and `debug_enable` forced on in `keyboard_post_init_user`) after backspace started firing unexpectedly right after typing a NUM-layer character followed immediately by `-`. The trace showed `NUM_BSP` down, `MSE_TAB`'s position down 98ms later (good overlap), `NUM_BSP` up at 142ms (still under `TAPPING_TERM`, so it resolved as a tap → Backspace) — all before `MSE_TAB`'s position was released. Enabled per-key on the five thumb keys that reach layer-shifted characters on the opposite thumb; left off `NAV_SPC` (commit `5df8847`). Reverted after ordinary typing started producing stray NUM-layer digits (e.g. `0` from `NAV_SPC`) with the intended Backspace silently swallowed — judged worse than the stray-Backspace case it fixed, since that case only misfired on deliberate cross-thumb chords while this one misfired during plain prose.

