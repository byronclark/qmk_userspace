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

**Applies to:** All mod-taps, but only GUI/Ctrl/Shift keys return `true` from `get_permissive_hold()`. LALT keys (HM_R, HM_I) return `false`.

**What it does:** When enabled for a key, a nested keypress (pressing another key while the mod-tap is held) immediately resolves the mod-tap as a hold, without waiting for TAPPING_TERM. When disabled for a key, a hold only fires after TAPPING_TERM expires.

| Symptom | Direction |
|---------|-----------|
| Common bigrams trigger Option on macOS (e.g. `it` → Option+T, `re` → Option+E) | Disable permissive hold for that LALT key |
| Intentional LALT chord requires awkward deliberate hold | Re-enable permissive hold for that key (accepting the bigram false trigger) |
| Other modifier (GUI/Ctrl/Shift) fails to fire on fast nested keypresses | That key may have permissive hold inadvertently disabled |

**History:** Started with global `PERMISSIVE_HOLD`. Switched to `PERMISSIVE_HOLD_PER_KEY` and disabled for HM_R and HM_I after the `it` bigram (e.g. "sitting") was producing Option+T on macOS. Flow tap was considered but rejected because it previously caused Ctrl false negatives when applied to non-pinky keys.

## FLOW_TAP_TERM (currently 100ms)

**Applies to:** Pinky GUI keys only (HM_A, HM_O) via `get_flow_tap_term()`. Returns 0 (disabled) for all other mod-taps.

**What it does:** If the previous keypress was within this window, the mod-tap resolves as a tap regardless of other heuristics. Prevents false modifier activation during fast typing rolls.

| Symptom | Direction | Example |
|---------|-----------|---------|
| GUI triggers during fast typing through A or O | Decrease | Typing "star" or "boat" activates GUI |
| GUI+key shortcut fails after typing (registers as plain letter) | Increase | Pause after typing, hit GUI+Tab, get `a` instead |

**History:** Was 150, reduced to 120. Disabled for Shift (T/N) and Ctrl (S/E) keys because it caused false taps when those modifiers were intended. Reduced from 120 to 100 to fix remaining GUI false taps.

## QUICK_TAP_TERM (currently 80ms for thumb keys, 120ms for others)

**Applies to:** Thumb layer-tap keys (NAV_SPC, NUM_BSP, SYM_ENT, FUN_DEL, MED_ESC, MSE_TAB) via `get_quick_tap_term()`.

**What it does:** After tapping a key, if you press it again within this window, QMK registers a repeat tap instead of evaluating hold. Lower values require faster double-taps to repeat.

| Symptom | Direction | Example |
|---------|-----------|---------|
| Accidental repeated taps on thumb keys (double space, double backspace) | Decrease | Pressing space twice in quick succession when only one was intended |
| Can't intentionally repeat thumb keys fast enough | Increase | Want to tap-tap-tap space quickly but second tap activates layer |

**History:** Global default was 150, reduced to 120. Thumb keys use hardcoded 80ms; HM_E returns 0.
