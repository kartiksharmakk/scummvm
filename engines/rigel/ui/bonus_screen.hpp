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

#include "rigel/data/bonus.hpp"
#include "rigel/engine/timing.hpp"
#include "rigel/frontend/game_mode.hpp"
#include "rigel/ui/menu_element_renderer.hpp"

#include <functional>
#include <set>


namespace Rigel {

namespace ui {
class BonusScreen {
public:
	BonusScreen(
		GameMode::Context context,
		const std::set<data::Bonus> &achievedBonuses,
		int scoreBeforeAddingBonuses);

	void handleEvent(const SDL_Event &event);
	void updateAndRender(engine::TimeDelta dt);

	bool finished() const { return mState.mIsDone; }

private:
	struct State {
		explicit State(const int score)
			: mScore(score) {
		}

		int mScore;
		std::string mRunningText;
		bool mIsDone = false;
	};

	struct Event {
		engine::TimeDelta mTime;
		std::function<void(State &)> mAction;
	};

	engine::TimeDelta setupBonusSummationSequence(
		const std::set<data::Bonus> &achievedBonuses,
		IGameServiceProvider *pServiceProvider);
	engine::TimeDelta
	setupNoBonusSequence(IGameServiceProvider *pServiceProvider);
	void updateSequence(engine::TimeDelta timeDelta);

private:
	State mState;

	engine::TimeDelta mElapsedTime = 0.0;
	std::vector<Event> mEvents;
	std::size_t mNextEvent = 0;

	renderer::Texture mBackgroundTexture;
	ui::MenuElementRenderer *mpTextRenderer;
};

} // namespace ui
} // namespace Rigel
