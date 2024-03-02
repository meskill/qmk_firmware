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

#include QMK_KEYBOARD_H
#include "layout.h"
#include "macro.h"

bool process_macro(uint16_t keycode, keyrecord_t *record) {
    bool down = record->event.pressed;
    int mods = get_mods();
    bool is_shift = mods & MOD_MASK_SHIFT;

    switch (keycode) {
        case RESET_STATE:
            if (down) {
                layer_move(0);
                SWTC_EN();
            }
            break;
        case SEND_I:
            if (down) {
                SEND_STRING("I");
            }
            break;
        case SEND_THE:
            if (down) {
                if (is_caps_word_on()) {
                    SEND_STRING("THE");
                } else if (is_shift) {
                    SEND_STRING("The");
                } else {
                    SEND_STRING("the");
                }
            }
            break;
        case KC_GRV:
            if (down && is_shift) {
                del_mods(mods);
                SEND_STRING("```");
                add_mods(mods);
                return false;
            }
            break;
        case SEND_ARR:
            if (down) {
                if (is_shift) {
                    del_mods(mods);
                    SEND_STRING("=>");
                    add_mods(mods);
                } else {
                    SEND_STRING("->");
                }
            }
            break;
        case SEND_TBFH: {
            if (down) {
                SEND_STRING("::<>");
                tap_code16(KC_LEFT);
            }
            break;
        }
    }

    return true;
}