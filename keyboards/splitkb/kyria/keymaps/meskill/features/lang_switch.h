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

#include QMK_KEYBOARD_H
#include "layout.h"

#ifndef LANG_SWITCH_TIMEOUT
#    define LANG_SWITCH_TIMEOUT 120000 // default is 2 minutes
#endif

bool process_lang_switch(uint16_t keycode, keyrecord_t *record);

void lang_switch_task(void);

void lang_switch_start(void);

void lang_switch_stop(void);
