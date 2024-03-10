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
#include "keymap_russian.h"
#include "chords.h"
#include "layout.h"
#include "macro.h"
#include "tap_dance.h"

const uint16_t PROGMEM ru_layer[] = {LALT_T(S_LCBR), LT(SYM, S_RBRC), COMBO_END};
const uint16_t PROGMEM ru_layer_word[] = {KC_SPC, KC_BSPC, COMBO_END};
const uint16_t PROGMEM ru_yo[] = {RU_SHTI, RU_A, COMBO_END};
const uint16_t PROGMEM ru_ha[] = {RU_ZE, RU_O, COMBO_END};
const uint16_t PROGMEM ru_e[] = {RU_ZHE, RU_O, COMBO_END};

combo_t key_combos[] = {
    [C_RU_LAYER] = COMBO(ru_layer, TG(RU)),
    [C_RU_LAYER_WORD] = COMBO(ru_layer_word, QK_LANG_WORD_TOGGLE),
    [C_RU_YO] = COMBO(ru_yo, RU_YO),
    [C_RU_HA] = COMBO(ru_ha, RU_HA),
    [C_RU_E] = COMBO(ru_e, RU_E),
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case C_RU_YO:
        case C_RU_HA:
        case C_RU_E:
            if (IS_LAYER_ON(RU)) {
                return true;
            }
            return false;
    }

    return true;
}