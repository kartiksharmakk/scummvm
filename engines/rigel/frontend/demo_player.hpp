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
#include "rigel/rigel.h"


/* Copyright (C) 2020, Nikolai Wuttke. All rights reserved.
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

#include "rigel/data/player_model.hpp"
#include "rigel/engine/timing.hpp"
#include "rigel/frontend/game_mode.hpp"
#include "rigel/game_logic_common/input.hpp"

#include <memory>
#include <vector>


namespace Rigel {
namespace game_logic {
class GameWorld_Classic;

struct DemoInput {
	PlayerInput mInput;
	bool mNextLevel;
};

class DemoPlayer {
public:
	explicit DemoPlayer(GameMode::Context context);
	~DemoPlayer();

	DemoPlayer(DemoPlayer &&);
	DemoPlayer &operator=(DemoPlayer &&);

	void updateAndRender(engine::TimeDelta dt);

	bool isFinished() const;

private:
	GameMode::Context mContext;
	data::PersistentPlayerState mPersistentPlayerState;

	std::vector<DemoInput> mFrames;
	std::size_t mCurrentFrameIndex = 1;
	std::size_t mLevelIndex = 0;
	engine::TimeDelta mElapsedTime = 0;

	std::unique_ptr<GameWorld_Classic> mpWorld;
};

} // namespace game_logic
} // namespace Rigel
