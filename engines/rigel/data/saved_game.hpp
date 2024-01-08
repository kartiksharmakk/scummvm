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

/* Copyright (C) 2019, Nikolai Wuttke. All rights reserved.
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

#include "rigel/data/game_session_data.hpp"
#include "rigel/data/player_model.hpp"

#include <array>
#include "rigel/3party/tloptional/include/tl/optional.hpp"
#include <string>


namespace Rigel {
namespace data {
constexpr auto NUM_SAVE_SLOTS = 8u;

struct SavedGame {
	GameSessionId mSessionId;
	TutorialMessageState mTutorialMessagesAlreadySeen;
	std::string mName;
	WeaponType mWeapon = WeaponType::Normal;
	int mAmmo = 0;
	int mScore = 0;
};

using SaveSlotArray = std::array<tl::optional<SavedGame>, NUM_SAVE_SLOTS>;
} // namespace data
} // namespace Rigel
