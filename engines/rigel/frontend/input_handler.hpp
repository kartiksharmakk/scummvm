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

#include "rigel/base/spatial_types.hpp"
#include "rigel/base/warnings.hpp"
#include "rigel/game_logic_common/input.hpp"

RIGEL_DISABLE_WARNINGS
#include <SDL.h>
RIGEL_RESTORE_WARNINGS

#include <vector>


namespace Rigel
{

namespace data
{
struct GameOptions;
}


class InputHandler
{
public:
  enum class MenuCommand
  {
    None,
    QuickSave,
    QuickLoad
  };

  explicit InputHandler(const data::GameOptions* pOptions);

  MenuCommand handleEvent(const SDL_Event& event, bool playerInShip);
  void reset();

  game_logic::PlayerInput fetchInput();

private:
  MenuCommand handleKeyboardInput(const SDL_Event& event);
  MenuCommand handleControllerInput(const SDL_Event& event, bool playerInShip);

  game_logic::PlayerInput mPlayerInput;
  base::Vec2 mAnalogStickVector;
  const data::GameOptions* mpOptions;
  bool mQuickSaveModifierHeld = false;
};

} // namespace rigel
