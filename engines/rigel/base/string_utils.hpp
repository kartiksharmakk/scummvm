/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* Copyright (C) 2021, Nikolai Wuttke. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "rigel/rigel.h"

#pragma once

#include <string>
#include <vector>


//std::string is only available in C++11 , temporarily replaced it with std::string  .
//need to use Common::String for it eventually

namespace Rigel
{
namespace strings {
/** Split a string based on a single char delimiter and return the output
 */
[[nodiscard]] std::vector<std::string>
split(std::string input, char delimiter);

/** Checks if an input string has the given prefix
 */
[[nodiscard]] bool
startsWith(std::string input, std::string prefix) noexcept;

/** Removes all occurences of 'what' from the left of the input, until any
 * non-'what' is found
 *
 * Does everything inplace.
 */


/** Like trimLeft, but works for temporaries/r-values (returns a new value) */
[[nodiscard]] std::string
trimLeft(std::string input, const char *what = "\n\r\t ");

/** Removes all occurences of 'what' from the right of the input, until any
 * non-'what' is found
 *
 * Does everything inplace.
 */


/** Like trimRight, but works for temporaries/r-values (returns a new value) */
[[nodiscard]] std::string
trimRight(std::string input, const char *what = "\n\r\t ");

/** Removes all occurences of 'what' from the right and left of the input, until
 * any non-'what' is found
 *
 * Does everything inplace.
 */


/** Like trim, but works for temporaries/r-values (returns a new value) */
[[nodiscard]] std::string
trim(std::string input, const char *what = "\n\r\t ");

[[nodiscard]] std::string toUppercase(std::string input);

[[nodiscard]] std::string toLowercase(std::string input);

} // namespace strings
} // namespace rigel::strings

