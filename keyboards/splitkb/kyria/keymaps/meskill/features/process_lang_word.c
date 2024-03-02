/* Copyright 2023 meskill (https://github.com/meskill)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "process_lang_word.h"
#include "process_auto_shift.h"
#include "lang_word.h"
#include "keycodes.h"
#include "quantum_keycodes.h"
#include "modifiers.h"
#include "timer.h"
#include "action_tapping.h"
#include "action_util.h"
#include "macro.h"

bool process_lang_word(uint16_t keycode, keyrecord_t* record) {
    if (keycode == QK_LANG_WORD_TOGGLE) {
        if (record->event.pressed) {
            lang_word_toggle();
        }
        return false;
    }

    if (!is_lang_word_on()) {
        return true;
    }

#if LANG_WORD_IDLE_TIMEOUT > 0
    lang_word_reset_idle_timer();
#endif // LANG_WORD_IDLE_TIMEOUT > 0

    // From here on, we only take action on press events.
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        // Ignore MO, TO, TG, TT, and OSL layer switch keys.
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_TRI_LAYER_LOWER ... QK_TRI_LAYER_UPPER:
        // Ignore AltGr.
        case KC_RALT:
        case KC_LSFT:
        case KC_RSFT:
        case OSM(MOD_RALT):
            if (QK_TOGGLE_LAYER_GET_LAYER(keycode) == LANG_WORD_LAYER) {
                lang_word_off();
            }
            return true;

#ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            break;

#    ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#    endif // NO_ACTION_LAYER
            if (record->tap.count == 0) {
                return true;
            }
            keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            break;
#endif // NO_ACTION_TAPPING

#ifdef SWAP_HANDS_ENABLE
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            // Note: IS_SWAP_HANDS_KEYCODE() actually tests for the special action keycodes like SH_TOGG, SH_TT, ...,
            // which currently overlap the SH_T(kc) range.
            if (IS_SWAP_HANDS_KEYCODE(keycode)
#    ifndef NO_ACTION_TAPPING
                || record->tap.count == 0
#    endif // NO_ACTION_TAPPING
            ) {
                return true;
            }
            keycode = QK_SWAP_HANDS_GET_TAP_KEYCODE(keycode);
            break;
#endif // SWAP_HANDS_ENABLE
    }

    return true;
}

void post_process_lang_word(uint16_t keycode, keyrecord_t* record) {
    if (!lang_word_press_user(keycode)) {
        dprintf("disable lang_word by lang_word_press_user code: %x\n", keycode);
        lang_word_off();
    }
}

__attribute__((weak)) bool lang_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Lang Word.
        case KC_A ... KC_Z:
        case KC_MINS:
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Lang Word.
    }
}
