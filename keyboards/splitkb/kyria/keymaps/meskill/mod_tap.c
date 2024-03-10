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

#include "mod_tap.h"
#include "keymap_russian.h"
#include "tap_dance.h"

bool process_mod_tap(uint16_t keycode, keyrecord_t *record) {
    bool down = record->event.pressed;
    bool tap = record->tap.count > 0;
    int mods = get_mods() | get_oneshot_mods() | get_dance_mods();

    if (!tap) return true;

    uint16_t code = 0;

    switch (keycode) {
        case LT(WIN, KC_MINS):
            // need custom check for caps word since we override behavior of key
            // here and without this we will register `-` instead of `_`
            // because mods for caps_word are registered later
            code = (mods & MOD_MASK_SHIFT) || is_caps_word_on() ? KC_UNDS : KC_MINS;
            break;
        case LT(MDA, S_QST): {
            code = (mods & MOD_MASK_SHIFT) ? S_EXL : S_QST;
            break;
        }
        case LT(FN, S_DQOT): {
            if (mods & MOD_MASK_SHIFT) {
                // call default behavior that will ignore SHIFT
                // due to caveats but that's exactly what we need
                return true;
            }

            code = S_DQOT;
            break;
        }
        // mod-tap fix for shift keycodes
        case LCTL_T(KC_LPRN):
        case LT(NAV, KC_RPRN): {
            code = LSFT(QK_MOD_TAP_GET_TAP_KEYCODE(keycode));
            break;
        }
        // mod-tap fix for ralt keycodes
        case LALT_T(S_LBRC): {
            code = RALT(QK_MOD_TAP_GET_TAP_KEYCODE(keycode));
            break;
        }
        // mod-tap fix for shift+ralt keycodes
        case LGUI_T(S_RCBR): {
            code = LSFT(RALT(QK_MOD_TAP_GET_TAP_KEYCODE(keycode)));
            break;
        }
        default:
            return true;
    }

    if (down) register_code16(code);
    else unregister_code16(code);

    return false;
}