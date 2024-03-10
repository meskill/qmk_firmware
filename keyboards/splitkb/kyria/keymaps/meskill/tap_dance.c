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

// borrowed code from https://docs.qmk.fm/#/feature_tap_dance?id=introduction
td_state_t cur_dance(tap_dance_state_t *state) {
    bool interrupted = state->interrupted;

    if (state->count == 1) {
        if (interrupted || state->pressed) return TD_SINGLE_HOLD;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_TAP;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

#define ACTION_TD(fn_finished, fn_reset) \
    { .fn = {NULL, fn_finished, fn_reset}, .user_data = (void *)&((td_tap_t){true, TD_NONE}), }

// end of borrowed code

void sft_finished(tap_dance_state_t *state, void *user_data) {
    td_tap_t *tap_state = (td_tap_t *)user_data;

    tap_state->state = cur_dance(state);

    if (state->interrupted) {
        if (IS_QK_LAYER_TAP(state->interrupting_keycode)) {
            // adding oneshot mods since for QK_LAYER_TAP keys actual tap could be registered
            // later after the SHIFT key is already released breaking original intention
            add_oneshot_mods(MOD_BIT(KC_LSFT));
            return;
        }
    }

    switch (tap_state->state) {
        case TD_SINGLE_TAP: tap_code16(S_LCBR); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: caps_word_toggle(); break;
        case TD_DOUBLE_HOLD: register_code16(S_LCBR); break;
        default: break;
    }
}

void sft_reset(tap_dance_state_t *state, void *user_data) {
    td_tap_t *tap_state = (td_tap_t *)user_data;

    switch (tap_state->state) {
        case TD_SINGLE_HOLD:
            dance_mods = MOD_MASK_SHIFT;
            unregister_code(KC_LSFT);
            reset_dance_timer();
            break;
        case TD_DOUBLE_HOLD: unregister_code16(S_LCBR); break;
        default: break;
    }
    tap_state->state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SFT] = ACTION_TD(sft_finished, sft_reset),
};


uint8_t get_dance_mods(void) {
    if (timer_expired32(timer_read32(), timer)) {
        dance_mods = 0;
    }

    return dance_mods;
}