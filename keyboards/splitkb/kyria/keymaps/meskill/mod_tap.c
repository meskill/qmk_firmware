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

bool process_mod_tap(uint16_t keycode, keyrecord_t *record) {
    bool down = record->event.pressed;
    bool tap = down && record->tap.count > 0;
    int mods = get_mods() | get_oneshot_mods();

    switch (keycode) {
        // mod-tap fix for media layer
        case LT(MDA, S_QST):
            if (tap) {
                if (mods & MOD_MASK_SHIFT) {
                    tap_code16(S_EXL);
                } else {
                    tap_code16(S_QST);
                }
                return false;
            }
            break;
        // mod-tap fix for shift keycodes
        case LCTL_T(KC_LPRN): {
            if (tap) {
                tap_code16(LSFT(QK_MOD_TAP_GET_TAP_KEYCODE(keycode)));
                return false;
            }

            break;
        }
        case LT(FN, S_DQOT): {
            if (tap) {
                if (mods & MOD_MASK_SHIFT) {
                    break;
                } else {
                    tap_code16(S_DQOT);
                }
                return false;
            }

            break;
        }
        // mod-tap fix for ralt keycodes
        case LALT_T(S_LBRC): {
            if (tap) {
                tap_code16(RALT(QK_MOD_TAP_GET_TAP_KEYCODE(keycode)));
                return false;
            }
            break;
        }
        // mod-tap fix for shift+ralt keycodes
        case LGUI_T(S_RCBR): {
            if (tap) {
                tap_code16(LSFT(RALT(QK_MOD_TAP_GET_TAP_KEYCODE(keycode))));
                return false;
            }

            break;
        }
    }

    return true;
}