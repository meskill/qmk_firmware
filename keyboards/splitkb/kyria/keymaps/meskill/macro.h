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

#pragma once

enum custom_keycodes {
    SEND_I = SAFE_RANGE,
    SEND_THE,
    SEND_TRGRV,
    SEND_ARR,
    SEND_TBFH,
    QK_LANG_WORD_TOGGLE
};

bool process_macro(uint16_t keycode, keyrecord_t *record);