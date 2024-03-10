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
#include "keymap_russian.h"
#include "layout.h"
#include "tap_dance.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [EN] = LAYOUT(
      KC_ESC         ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,                                         KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  , KC_P  ,  LT(MDA, S_QST)  ,
      LT(WIN, KC_MINS)        ,  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,                                         KC_H  ,  KC_J  ,  KC_K  ,  KC_L  , SEND_THE ,  LT(FN, S_DQOT) ,
      KC_DOT,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,  KC_APP, MO(STP),           MO(STP),  LAG(KC_PSCR),  KC_N  ,  KC_M  ,  SEND_I ,  KC_QUOT , KC_COMM,  KC_SLSH  ,
                        LALT_T(KC_LBRC), LCTL_T(KC_LPRN), KC_SPC, TD(TD_SFT),  KC_TAB,            KC_ENT, LGUI_T(S_RCBR),  KC_BSPC,   LT(NAV, KC_RPRN), LT(SYM, S_RBRC)
    ),

		[RU] = LAYOUT(
      _______  ,  RU_SHTI,  RU_TSE  ,  RU_U  ,  RU_KA ,  RU_IE ,                                         RU_EN  ,  RU_GHE ,  RU_SHA , RU_SHCH ,  RU_ZE  ,  _______  ,
      _______  ,  RU_EF  ,  RU_YERU ,  RU_VE ,  RU_A  ,  RU_PE ,                                         RU_ER  ,  RU_O   ,  RU_EL  , RU_DE   ,  RU_ZHE ,  _______ ,
      RU_DOT ,  RU_YA  ,  RU_CHE  ,  RU_ES ,  RU_EM ,  RU_I  ,  _______, _______,        _______, _______ ,  RU_TE  ,  RU_SOFT,  RU_BE  , RU_YU   ,  RU_COMM ,  S_SLH  ,
                     LALT_T(S_LBRC), _______,  _______, _______, _______,                 _______, _______, _______, _______, _______
    ),

		[SYM] = LAYOUT(
      _______, KC_PERC, KC_TILD, S_EUR, KC_GRV, _______,                                                 KC_PLUS, KC_7, KC_8, KC_9, KC_CIRC, _______ ,
      _______, KC_AT, KC_AMPR, KC_DLR, KC_HASH, SEND_ARR  ,                                                 KC_ASTR, KC_4, KC_5, KC_6, KC_EQL, _______,
      _______, KC_LT, KC_PIPE, KC_EQL, KC_GT, SEND_TBFH, _______, _______,            _______, _______,  KC_0   , KC_1, KC_2, KC_3, _______ , _______,
                              _______, _______, _______, _______, _______,                              _______, _______, _______, _______, _______
    ),

		[NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                        _______, KC_PGUP, KC_UP, KC_HOME, LSA(KC_RGHT), _______,
      _______, _______, _______, _______, _______, _______,                                         _______, KC_LEFT, KC_DOWN, KC_RGHT, LCTL(KC_L), _______,
      _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, KC_PGDN, LCTL(KC_LBRC),  KC_END, LSA(KC_LEFT), _______,
                                _______, _______, _______, _______, _______,         _______, _______,  KC_DEL, _______, _______
    ),

    [FN] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                                 _______, KC_F7, KC_F8, KC_F9, KC_F10, _______ ,
      _______, _______, _______, _______, _______, _______,                                                 _______, KC_F4, KC_F5, KC_F6, KC_F11, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______,  _______, KC_F1, KC_F2, KC_F3, KC_F12, _______,
                              _______, _______, _______, _______, _______,                              _______, _______, _______, _______, _______
    ),

    [WIN] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                                 _______, _______, _______, _______, _______, _______ ,
      _______, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5),                                               _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______,  _______, _______, _______, _______, _______ , _______,
                              _______, _______, _______, _______, _______,                              _______, _______, _______, _______, _______
    ),

		[GAME] = LAYOUT(
      KC_ESC, KC_1, KC_Q, KC_W, KC_E, KC_R,                                                             _______, _______, _______, _______, _______, _______,
      KC_G, KC_2, KC_A, KC_S, KC_D, KC_F,                                                              _______, _______, _______, _______, _______, _______,
      KC_B , KC_3, KC_Z, KC_X, KC_C, KC_V, KC_O, KC_TAB,                         _______, _______, _______, _______, _______, _______, _______, _______,
                  KC_T, KC_LCTL, KC_LSFT, KC_SPC, SH_T(KC_I),                        _______, _______, _______, _______, _______
    ),

		[MDA] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                               _______, _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PLAY_PAUSE, _______,
      _______, _______, _______, _______, _______, _______,                                 _______, _______, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, KC_MEDIA_SELECT, _______, _______, _______,
                _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______
    ),

		[STP] = LAYOUT(
      QK_BOOT, QK_CLEAR_EEPROM, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                              RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD, _______,
      DB_TOGG, _______, _______, _______, _______, _______, RESET_STATE, _______,           _______, RESET_STATE, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                _______, _______, _______, _______, TG(GAME),             TG(GAME), _______, _______, TG(NAV), TG(SYM)
    )

//  /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
