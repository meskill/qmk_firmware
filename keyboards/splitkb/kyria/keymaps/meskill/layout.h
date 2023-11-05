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

#define S_QST RSA(KC_SLSH)
#define S_EXL LSFT(KC_1)
#define S_CLN RSA(KC_SCLN)
#define S_SCLN RALT(KC_SCLN)
#define S_QOT RALT(KC_QUOT)
#define S_DQOT RSA(KC_DQT)
#define S_SLH RALT(KC_SLSH)
#define S_BSLH KC_BSLS
#define S_LBRC RALT(KC_LBRC)
#define S_RBRC RALT(KC_RBRC)
#define S_LCBR RALT(KC_LCBR)
#define S_RCBR RALT(KC_RCBR)
#define S_EUR RALT(KC_5)

#define SWTC_EN() tap_code16(LSA(KC_1))
#define SWTC_RU() tap_code16(LSA(KC_2))
