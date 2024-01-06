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



/* Copyright (C) 2017, Nikolai Wuttke. All rights reserved.
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
#include "rigel/data/sound_ids.hpp"
#include "rigel/frontend/command_line_options.hpp"
#include "rigel/sdl_utils/ptr.hpp"

#include <SDL_gamecontroller.h>

//TODO Scummvm replacement for filesystem
#if 0
#include <filesystem>
#endif
#include <string>
#include <vector>


namespace Rigel
{
namespace data
{
struct SavedGame;
}
}

namespace Rigel
{

struct UnrecognizedController
{
  UnrecognizedController(std::string name, std::string guid)
    : mName(std::move(name))
    , mGuid(std::move(guid))
  {
  }

  std::string mName;
  std::string mGuid;
};


struct GameControllerInfo
{
  std::vector<sdl_utils::Ptr<SDL_GameController>> mGameControllers;
  std::vector<UnrecognizedController> mUnrecognizedControllers;
};


/** Interface for functionality available to game modes */
#include "rigel/rigel.h"
struct IGameServiceProvider
{
  virtual ~IGameServiceProvider() = default;

  // Blocking calls
  virtual void fadeOutScreen() = 0;
  virtual void fadeInScreen() = 0;

  // Non-blocking calls
  virtual void playSound(data::SoundId id) = 0;
  virtual void stopSound(data::SoundId id) = 0;
  virtual void stopAllSounds() = 0;
  virtual void playMusic(const std::string& name) = 0;
  virtual void stopMusic() = 0;
  virtual void scheduleGameQuit() = 0;
  #if 0
  virtual void switchGamePath(const std::filesystem::path& newGamePath) = 0;
  #endif
  virtual void markCurrentFrameAsWidescreen() = 0;
  virtual bool isSharewareVersion() const = 0;
  virtual const CommandLineOptions& commandLineOptions() const = 0;
  virtual const GameControllerInfo& gameControllerInfo() const = 0;
};

} // namespace rigel
