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
#include "rgb.h"
#include "features/lang_word.h"

// Effects overrides
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {80, 30, 5};

enum {
    // RGB_ ru and en are swapped as en base layer is always activated
    // and I need to overwrite ru layer with en so it should be higher in rgb sense
    RGB_RU = EN,
    RGB_EN = RU,
    RGB_DBG = MDA + 1,
    RGB_CWRD,
    RGB_RESET
};

const rgblight_segment_t PROGMEM en_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SPLIT_LED_MIRROR(3, 1, HSV_BLUE),
    SPLIT_LED_MIRROR(5, 1, HSV_BLUE)
);

const rgblight_segment_t PROGMEM ru_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SPLIT_LED_MIRROR(3, 1, HSV_RED),
    SPLIT_LED_MIRROR(5, 1, HSV_RED)
);

const rgblight_segment_t PROGMEM sym_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SPLIT_LED_MIRROR(0, 1, HSV_GOLDENROD),
    SPLIT_LED_MIRROR(1, 1, HSV_GOLDENROD)
);

const rgblight_segment_t PROGMEM nav_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SPLIT_LED_MIRROR(0, 1, HSV_GREEN),
    SPLIT_LED_MIRROR(1, 1, HSV_GREEN)
);

const rgblight_segment_t PROGMEM fn_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SPLIT_LED_RIGHT(1, 1, HSV_PURPLE),
    SPLIT_LED_RIGHT(3, 1, HSV_PURPLE),
    SPLIT_LED_RIGHT(5, 1, HSV_PURPLE)
);

const rgblight_segment_t PROGMEM win_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SPLIT_LED_LEFT(1, 1, HSV_AZURE),
    SPLIT_LED_LEFT(3, 1, HSV_AZURE),
    SPLIT_LED_LEFT(5, 1, HSV_AZURE)
);

const rgblight_segment_t PROGMEM game_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SPLIT_LED_MIRROR(0, 1, HSV_RED),
    SPLIT_LED_MIRROR(1, 1, HSV_RED),
    SPLIT_LED_MIRROR(2, 1, HSV_MAGENTA),
    SPLIT_LED_MIRROR(3, 1, HSV_MAGENTA),
    SPLIT_LED_MIRROR(4, 1, HSV_RED),
    SPLIT_LED_MIRROR(5, 1, HSV_RED)
);

const rgblight_segment_t PROGMEM mda_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SPLIT_LED_RIGHT(0, 1, HSV_PINK),
    SPLIT_LED_RIGHT(2, 1, HSV_PINK),
    SPLIT_LED_RIGHT(4, 1, HSV_PINK)
);

const rgblight_segment_t PROGMEM debug_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SPLIT_LED_MIRROR(0, 6, HSV_WHITE)
);

const rgblight_segment_t PROGMEM cwrd_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SPLIT_LED_MIRROR(1, 1, HSV_WHITE)
);

const rgblight_segment_t PROGMEM reset_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SPLIT_LED_MIRROR(0, 6, HSV_BLUE)
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    [RGB_EN] = en_rgb_layer,
    [RGB_RU] = ru_rgb_layer,
    [SYM] = sym_rgb_layer,
    [NAV] = nav_rgb_layer,
    [FN] = fn_rgb_layer,
    [WIN] = win_rgb_layer,
    [GAME] = game_rgb_layer,
    [MDA] = mda_rgb_layer,
    [RGB_DBG] = debug_rgb_layer,
    [RGB_CWRD] = cwrd_rgb_layer,
    [RGB_RESET] = reset_rgb_layer
);

void rgblight_blink_layer_repeat_max(uint8_t layer, uint16_t duration_ms) {
    rgblight_blink_layer_repeat(layer, duration_ms, UINT8_MAX);
}

void keyboard_post_init_rgb(void) {
    rgblight_layers = rgb_layers;
}

static uint8_t previous_rgb_mode;

void layer_state_set_rgb(layer_state_t state) {
    if (!is_lang_word_on()) {
        rgblight_set_layer_state(RGB_RU, layer_state_cmp(state, RU));
    }
    rgblight_set_layer_state(SYM, layer_state_cmp(state, SYM));
    rgblight_set_layer_state(NAV, layer_state_cmp(state, NAV));
    rgblight_set_layer_state(FN, layer_state_cmp(state, FN));
    rgblight_set_layer_state(WIN, layer_state_cmp(state, WIN));
    rgblight_set_layer_state(MDA, layer_state_cmp(state, MDA));

    if (layer_state_cmp(state, GAME) && IS_LAYER_OFF(GAME)) {
        rgblight_blink_layer_repeat(GAME, 300, 5);
        previous_rgb_mode = rgblight_get_mode();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 4);
    } else if (IS_LAYER_ON(GAME) && !layer_state_cmp(state, GAME))   {
        rgblight_blink_layer_repeat(GAME, 300, 1);
        if (previous_rgb_mode) {
            rgblight_mode_noeeprom(previous_rgb_mode);
        }
    }
}

void post_process_record_rgb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_DEBUG_TOGGLE:
            rgblight_blink_layer_repeat(RGB_DBG, 200, debug_enable ? 3 : 1);
            break;
        case TO(EN):
            rgblight_blink_layer_repeat(RGB_RESET, 200, 3);
            break;
    }
}

void lang_word_set_user(bool active) {
    if (active) {
        rgblight_blink_layer_repeat_max(IS_LAYER_ON(RU) ? RGB_RU : RGB_EN, 500);
    } else {
        rgblight_unblink_layer(RGB_RU);
        rgblight_unblink_layer(RGB_EN);
    }
}

void caps_word_set_user(bool active) {
    if (active) {
        rgblight_blink_layer_repeat_max(RGB_CWRD, 500);
    } else {
        rgblight_unblink_layer(RGB_CWRD);
    }
}
