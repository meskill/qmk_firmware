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

#include <stdbool.h>

#ifndef LANG_WORD_IDLE_TIMEOUT
#    define LANG_WORD_IDLE_TIMEOUT 5000 // Default timeout of 5 seconds.
#endif

/** @brief Matrix scan task for Lang Word feature */
void lang_word_task(void);

#if LANG_WORD_IDLE_TIMEOUT > 0
/** @brief Resets timer for Lang Word idle timeout. */
void lang_word_reset_idle_timer(void);
#endif

/** @brief Activates Lang Word. */
void lang_word_on(void);

/** @brief Deactivates Lang Word. */
void lang_word_off(void);

/** @brief Toggles Lang Word. */
void lang_word_toggle(void);

/** @brief Gets whether currently active. */
bool is_lang_word_on(void);

/**
 * @brief Lang Word set callback.
 *
 * @param active True if Lang Word is active, false otherwise
 */
void lang_word_set_user(bool active);
