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

#pragma once

#include "rigel/assets/duke_script_loader.hpp"
#include "rigel/data/duke_script.hpp"
#include "rigel/frontend/game_mode.hpp"
#include "rigel/ui/duke_script_runner.hpp"
#include "rigel/ui/options_menu.hpp"

#include <optional>

#if 0
namespace Rigel
{

class MenuMode : public GameMode
{
public:
  explicit MenuMode(Context context);

  std::unique_ptr<GameMode> updateAndRender(
    engine::TimeDelta dt,
    const std::vector<SDL_Event>& events) override;

private:
  enum class MenuState
  {
    AskIfQuit,
    ChooseInstructionsOrStory,
    EpisodeNotAvailableMessage,
    EpisodeNotAvailableMessageHighScores,
    NoSavedGameInSlotMessage,
    Instructions,
    MainMenu,
    OrderingInformation,
    RestoreGame,
    SelectHighscoresEpisode,
    SelectNewGameEpisode,
    SelectNewGameSkill,
    ShowCredits,
    ShowHiscores,
    Story
  };

  void handleEvent(const SDL_Event& event);
  void enterMainMenu();
  std::unique_ptr<GameMode>
    navigateToNextMenu(const ui::DukeScriptRunner::ExecutionResult& result);

private:
  Context mContext;
  std::optional<ui::OptionsMenu> mOptionsMenu;
  MenuState mMenuState = MenuState::MainMenu;
  int mChosenEpisode = 0;
};

} // namespace rigel
#endif
