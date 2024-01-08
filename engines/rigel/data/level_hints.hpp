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

/* Copyright (C) 2018, Nikolai Wuttke. All rights reserved.
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

#include "rigel/3party/tloptional/include/tl/optional.hpp"

#include <string>
#include <utility>
#include <vector>


namespace Rigel
{
namespace data {
struct Hint {
	Hint(const int episode, const int level, std::string message)
		: mEpisode(episode), mLevel(level), mMessage(std::move(message)) {
	}

	int mEpisode;
	int mLevel;
	std::string mMessage;
};

struct LevelHints {
	LevelHints() = default;
	explicit LevelHints(std::vector<Hint> hints)
		: mHints(std::move(hints)) {
	}
	
	tl::optional<std::string> getHint(int episode, int level) const;
	std::vector<Hint> mHints;
};

} // namespace data
} // namespace rigel::data
