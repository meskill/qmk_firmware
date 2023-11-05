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
#include <stdint.h>
#include "lang_word.h"
#include "timer.h"
#include "action.h"
#include "action_util.h"
#include "layout.h"

/** @brief True when Lang Word is active. */
static bool lang_word_active = false;

#if LANG_WORD_IDLE_TIMEOUT > 0
// Constrain timeout to a sensible range. With 16-bit timers, the longest
// timeout possible is 32768 ms, rounded here to 30000 ms = half a minute.
#    if LANG_WORD_IDLE_TIMEOUT < 100 || LANG_WORD_IDLE_TIMEOUT > 30000
#        error "LANG_WORD_IDLE_TIMEOUT must be between 100 and 30000 ms"
#    endif

/** @brief Deadline for idle timeout. */
static uint16_t idle_timer = 0;

void lang_word_task(void) {
    if (lang_word_active && timer_expired(timer_read(), idle_timer)) {
        lang_word_off();
    }
}

void lang_word_reset_idle_timer(void) {
    idle_timer = timer_read() + LANG_WORD_IDLE_TIMEOUT;
}
#else
void lang_word_task(void) {}
#endif // LANG_WORD_IDLE_TIMEOUT > 0

void lang_word_on(void) {
    if (lang_word_active) {
        return;
    }

    dprint("enable lang_word\n");

    layer_invert(LANG_WORD_LAYER);
#if LANG_WORD_IDLE_TIMEOUT > 0
    lang_word_reset_idle_timer();
#endif // LANG_WORD_IDLE_TIMEOUT > 0

    lang_word_active = true;
    lang_word_set_user(true);
}

void lang_word_off(void) {
    if (!lang_word_active) {
        return;
    }

    dprint("disable lang_word\n");

    lang_word_active = false;
    lang_word_set_user(false);
    layer_invert(LANG_WORD_LAYER);
}

void lang_word_toggle(void) {
    if (lang_word_active) {
        lang_word_off();
    } else {
        lang_word_on();
    }
}

bool is_lang_word_on(void) {
    return lang_word_active;
}

__attribute__((weak)) void lang_word_set_user(bool active) {}
