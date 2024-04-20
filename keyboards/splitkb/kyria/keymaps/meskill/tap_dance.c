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

#include "tap_dance.h"

static uint32_t timer = 0;
static uint8_t dance_mods = 0;

void reset_dance_timer(void) {
    timer = timer_read32() + TAPPING_TERM;
}

uint8_t get_dance_mods(void) {
    if (timer_expired32(timer_read32(), timer)) {
        dance_mods = 0;
    }

    return dance_mods;
}

// borrowed code from https://docs.qmk.fm/#/feature_tap_dance?id=introduction
td_state_t cur_dance(tap_dance_state_t *state, bool hold_on_other_key_press) {
    bool interrupted = state->interrupted;

    if (state->count == 1) {
        if (interrupted) return hold_on_other_key_press ? TD_SINGLE_HOLD : TD_SINGLE_TAP;
        if (state->pressed) return TD_SINGLE_HOLD;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        return TD_SINGLE_TAP;
    }

    if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (interrupted) return hold_on_other_key_press ? TD_DOUBLE_HOLD : TD_DOUBLE_TAP;
        if (state->pressed) return TD_DOUBLE_HOLD;
        return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (interrupted) return hold_on_other_key_press ? TD_TRIPLE_HOLD : TD_TRIPLE_TAP;
        if (!state->pressed) return TD_TRIPLE_TAP;
        return TD_TRIPLE_HOLD;
    }

    return TD_UNKNOWN;
}

#define ACTION_TD(fn_finished, fn_reset) \
    { .fn = {NULL, fn_finished, fn_reset}, .user_data = (void *)&((td_tap_t){true, TD_NONE}), }

// end of borrowed code

tap_dance_action_t tap_dance_actions[] = {
};