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

#include "lang_switch.h"
#include "debug.h"

static bool is_lang_activated = false;
static bool invert_lang_on_release = false;
static uint32_t timer = 0;

void reset_timer(void) {
    timer = timer_read32() + LANG_SWITCH_TIMEOUT;
}

bool process_lang_switch(uint16_t keycode, keyrecord_t *record) {
    bool down = record->event.pressed;
    bool tap = down && record->tap.count > 0;

    if (is_lang_activated) {
        reset_timer();
    }

    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX: {
            if (tap) {
                return true;
            }

            uint16_t tap_mods = QK_MOD_TAP_GET_MODS(keycode);

            if (!(tap_mods & (MOD_LCTL | MOD_LGUI))) {
                return true;
            }

            if (down) {
                invert_lang_on_release = IS_LAYER_ON(LANG_SWITCH_LAYER);
                layer_off(LANG_SWITCH_LAYER);
                register_mods(tap_mods);
            } else {
                unregister_mods(tap_mods);

                if (invert_lang_on_release) {
                    layer_on(LANG_SWITCH_LAYER);
                }
            }

            return false;
        }
    }

    return true;
}

void lang_switch_task(void) {
    if (is_lang_activated && timer_expired32(timer_read32(), timer)) {
        dprint("lang_switch_timer expired\n");
        layer_invert(LANG_SWITCH_LAYER);
        lang_switch_stop();
    }
}

void lang_switch_start(void) {
    dprint("lang_switch_start\n");
    reset_timer();
    is_lang_activated = true;
}

void lang_switch_stop(void) {
    dprint("lang_switch_stop\n");
    is_lang_activated = false;
}