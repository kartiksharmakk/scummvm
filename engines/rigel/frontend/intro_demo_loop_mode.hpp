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

#include "rigel/assets/duke_script_loader.hpp"
#include "rigel/frontend/demo_player.hpp"
#include "rigel/frontend/game_mode.hpp"
#include "rigel/ui/apogee_logo.hpp"
#include "rigel/ui/intro_movie.hpp"

#include <memory>

//<variant> is C++17 exclusive
#if 0
#include <variant>
#endif

namespace Rigel
{

namespace ui
{
class DukeScriptRunner;
}


/** Implements the intro/credits/demo loop
 *
 * This is the non-interactive "demo" mode of Duke Nukem II. It keeps
 * repeating the following sequence until any key is pressed:
 *
 *   Intro movie -> Credits -> Ordering Info (if Shareware) -> in-game demos
 *     -> Apogee Logo
 *
 * This mode is entered when the user sits on the main menu for a certain
 * period of time without giving any input. It's also used for the game's
 * start, although it then starts on the Apogee Logo and includes the story
 * cutscene/animation.
 */
#include "rigel/rigel.h"
class IntroDemoLoopMode : public GameMode
{
public:
  enum class Type
  {
    Regular,
    DuringGameStart,
    AtFirstLaunch
  };

  /** Construct an IntroDemoLoopMode instance
   *
   * When the game starts, the behavior is slightly different from the normal
   * intro/demo loop: The Apogee Logo is shown first, and the story cutscene
   * is shown after the intro movie.
   * Normally, the Apogee Logo comes last, and the story is not shown.
   */
#include "rigel/rigel.h"
  IntroDemoLoopMode(Context context, Type type);
  #if 0
  std::unique_ptr<GameMode> updateAndRender(
    engine::TimeDelta dt,
    const std::vector<SDL_Event>& events) override;
  #endif
private:
  struct ScriptedStep
  {
  };
  struct Credits : ScriptedStep
  {
  };
  struct HypeScreen : ScriptedStep
  {
  };

  struct Story : ScriptedStep
  {
  };
  #if 0
  using Step = std::variant<
    ui::ApogeeLogo,
    ui::IntroMovie,
    Story,
    HypeScreen,
    Credits,
    game_logic::DemoPlayer>;
  #endif
  bool handleEvent(const SDL_Event& event);
  void startCurrentStep();
  void updateCurrentStep(engine::TimeDelta dt);
  bool isCurrentStepFinished() const;
  void advanceToNextStep();

  Context mContext;
  #if 0
  std::vector<Step> mSteps;
  #endif
  std::size_t mCurrentStep = 0;
};

} // namespace rigel
