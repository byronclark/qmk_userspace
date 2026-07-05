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

- **Kyria `n`-switch chatter:** bumped `DEBOUNCE` to 15ms with `DEBOUNCE_TYPE = sym_eager_pk` in the Kyria adapter (commit `0924fac`), reverted once the hotswap socket was resoldered. See that commit for the diagnostic details and the symptom-to-direction table; reapply if chatter returns.

