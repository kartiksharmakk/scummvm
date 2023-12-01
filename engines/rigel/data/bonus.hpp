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

#pragma once

#include "rigel/data/player_model.hpp"

#include <cstdint>
#include <set>


namespace Rigel {
namespace data {
constexpr int SCORE_ADDED_PER_BONUS = 100000;

// Enum values match the bonus numbers shown on the bonus screen
enum class Bonus : std::uint8_t {
	DestroyedAllCameras = 1,
	NoDamageTaken = 2,
	CollectedEveryWeapon = 3,
	CollectedAllMerchandise = 4,
	DestroyedAllSpinningLaserTurrets = 5,
	DestroyedAllFireBombs = 6,
	ShotAllBonusGlobes = 7
};

constexpr int asNumber(const Bonus bonus) {
	return static_cast<int>(bonus);
}

inline void addBonusScore(
	PersistentPlayerState &persistentPlayerState,
	const std::set<Bonus> &bonuses) {
	const auto numBonuses = static_cast<int>(bonuses.size());
	persistentPlayerState.giveScore(numBonuses * SCORE_ADDED_PER_BONUS);
}

} // namespace data
} // namespace Rigel
