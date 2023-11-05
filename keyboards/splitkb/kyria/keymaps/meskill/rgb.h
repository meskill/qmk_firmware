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

void post_process_record_rgb(uint16_t keycode, keyrecord_t *record);

void keyboard_post_init_rgb(void);

void layer_state_set_rgb(layer_state_t state);

#define SPLIT_RGBLED_NUM (RGBLED_NUM / 2)
#define SPLIT_LED_LEFT(start, count, color) {start, count, color}
#define SPLIT_LED_RIGHT(start, count, color) {SPLIT_RGBLED_NUM + (start % 2 == 0 ? SPLIT_RGBLED_NUM - 2 : SPLIT_RGBLED_NUM) - start - count + 1, count, color}

#define SPLIT_LED_MIRROR(start, count, color) \
  {start, count, color}, \
  {SPLIT_RGBLED_NUM + (start % 2 == 0 ? SPLIT_RGBLED_NUM - 2 : SPLIT_RGBLED_NUM) - start - count + 1, count, color}

