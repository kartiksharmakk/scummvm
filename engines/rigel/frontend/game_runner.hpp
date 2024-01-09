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

/* Copyright (C) 2016, Nikolai Wuttke. All rights reserved.
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

#include "rigel/base/spatial_types.hpp"
#include "rigel/base/warnings.hpp"
#include "rigel/data/bonus.hpp"
#include "rigel/data/saved_game.hpp"
#include "rigel/frontend/game_mode.hpp"
#include "rigel/frontend/input_handler.hpp"
#include "rigel/game_logic_common/igame_world.hpp"
#include "rigel/game_logic_common/input.hpp"
#include "rigel/ui/ingame_menu.hpp"

RIGEL_DISABLE_WARNINGS
#include <SDL.h>
RIGEL_RESTORE_WARNINGS

#include <memory>


namespace Rigel
{

class GameRunner
{
public:
  GameRunner(
    data::PersistentPlayerState* pPersistentPlayerState,
    const data::GameSessionId& sessionId,
    GameMode::Context context,

	#if 0
    tl::optional<base::Vec2> playerPositionOverride = tl::nullopt,
	#endif
    bool showWelcomeMessage = false);

  void handleEvent(const SDL_Event& event);
  void updateAndRender(engine::TimeDelta dt);
  bool needsPerElementUpscaling() const;

  bool levelFinished() const;
  bool gameQuit() const;
  tl::optional<data::SavedGame> requestedGameToLoad() const;

  std::set<data::Bonus> achievedBonuses() const;

private:
  float interpolationFactor(engine::TimeDelta dt) const;
  void updateWorld(engine::TimeDelta dt);
  bool updateMenu(engine::TimeDelta dt);
  void handleDebugKeys(const SDL_Event& event);
  void renderDebugText();

  GameMode::Context mContext;

  std::unique_ptr<game_logic::IGameWorld> mpWorld;
  InputHandler mInputHandler;
  engine::TimeDelta mAccumulatedTime = 0.0;
  ui::IngameMenu mMenu;
  bool mShowDebugText = false;
  bool mSingleStepping = false;
  bool mDoNextSingleStep = false;
  bool mLevelFinishedByDebugKey = false;
};

} // namespace rigel
