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

#include "keymap_russian.h"

const key_override_t delete = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t gamebar_record = ko_make_basic(MOD_MASK_GUI, LAG(KC_PSCR), LAG(KC_R));

#define EN_ONL (1<<EN)

const key_override_t colon_en = ko_make_with_layers(MOD_MASK_SHIFT, LT(WIN, KC_DOT), KC_COLN, EN_ONL);
const key_override_t semicolon_en = ko_make_with_layers(MOD_MASK_SHIFT, LT(FN, KC_COMM), KC_SCLN, EN_ONL);
const key_override_t backslash_en = ko_make_with_layers(MOD_MASK_SHIFT, KC_SLSH, S_BSLH, EN_ONL);

#define RU_ONL (1<<RU)

const key_override_t colon_ru = ko_make_with_layers(MOD_MASK_SHIFT, LT(WIN, RU_DOT), S_CLN, RU_ONL);
const key_override_t semicolon_ru = ko_make_with_layers(MOD_MASK_SHIFT, LT(FN, RU_COMM), S_SCLN, RU_ONL);
const key_override_t hardsign = ko_make_with_layers(MOD_MASK_SHIFT, RU_SOFT, RU_HARD, RU_ONL);
const key_override_t backslash_ru = ko_make_with_layers(MOD_MASK_SHIFT, S_SLH, S_BSLH, RU_ONL);

#define LANG EN_ONL | RU_ONL

const key_override_t exclamation = ko_make_with_layers(MOD_MASK_SHIFT, LT(MDA, S_QST), S_EXL, LANG);
const key_override_t quote = ko_make_with_layers(MOD_MASK_SHIFT, S_DQOT, S_QOT, LANG);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete,
    &gamebar_record,
    &colon_en,
    &colon_ru,
    &semicolon_en,
    &semicolon_ru,
    &hardsign,
    &backslash_en,
    &backslash_ru,
    &exclamation,
    &quote,
    NULL // Null terminate the array of overrides!
};

