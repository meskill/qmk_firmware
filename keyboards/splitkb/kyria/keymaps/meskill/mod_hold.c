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

#include "mod_hold.h"

bool process_mod_hold(uint16_t keycode, keyrecord_t *record) {
    bool down = record->event.pressed;
    bool tap = record->tap.count > 0;

    if (IS_LAYER_ON(WIN)) {
        switch (keycode) {
            case KC_1 ... KC_0: {
                if (down) {
                    register_code16(KC_LGUI);
                }
                break;
            }
            case LT(WIN, KC_MINS): {
                if (!tap && !down) {
                    unregister_code16(KC_LGUI);
                }
                break;
            }
        }

        return true;
    }

    return true;
}