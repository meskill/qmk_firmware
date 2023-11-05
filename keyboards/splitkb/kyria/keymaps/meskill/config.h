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

#if !defined(__ASSEMBLER__)
    enum layers {
        EN = 0,
        RU,
        SYM,
        NAV,
        FN,
        WIN,
        GAME,
        MDA,
        STP,
    };
#endif

#ifdef RGBLIGHT_ENABLE
    // hardware settings
    #define RGBLIGHT_SLEEP
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
    #define RGBLIGHT_TIMEOUT 600000
    // only underglow leds
    #undef RGBLED_NUM
    #define RGBLED_NUM 12
    #undef RGBLED_SPLIT
    #define RGBLED_SPLIT {6, 6}
    // mapped horizontally instead of default c-formed placement
    #define RGBLIGHT_LED_MAP {4, 2, 0, 1, 3, 5, 6+0, 6+2, 6+4, 6+5, 6+3, 6+1}

    // control on-controller led. Uncomment only in case if you want to control
    // only that leds as it will prevent from controlling on-keyboard leds
    // see https://docs.splitkb.com/hc/en-us/articles/5799904122012-Onboard-RGB
    // #undef WS2812_DI_PIN
    // #define WS2812_DI_PIN 25
    // #undef RGBLED_NUM
    // #define RGBLED_NUM 2
    // #undef RGBLED_SPLIT
    // #define RGBLED_SPLIT {1, 1}

    // control keyboard underglow
    #define SPLIT_LAYER_STATE_ENABLE
    #define RGBLIGHT_SPLIT
    #define RGBLIGHT_LAYERS
    #define RGBLIGHT_MAX_LAYERS 12
    #define RGBLIGHT_LAYERS_RETAIN_VAL
    #define RGBLIGHT_LAYER_BLINK

    // available effects
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    // #define RGBLIGHT_EFFECT_KNIGHT
    // #define RGBLIGHT_EFFECT_CHRISTMAS
    // #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    // #define RGBLIGHT_EFFECT_RGB_TEST
    // #define RGBLIGHT_EFFECT_ALTERNATING
    // #define RGBLIGHT_EFFECT_TWINKLE

    // dynamic settings configuration
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 10
    #define RGBLIGHT_VAL_STEP 10
    #ifndef RGBLIGHT_LIMIT_VAL
        #define RGBLIGHT_LIMIT_VAL 150
    #endif
#endif

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

#define TAPPING_TOGGLE 2
#define COMBO_SHOULD_TRIGGER

#define LANG_WORD_LAYER RU
#define LANG_SWITCH_LAYER RU

// debug
#define ACTION_DEBUG