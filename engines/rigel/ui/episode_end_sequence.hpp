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

#include "rigel/frontend/game_mode.hpp"
#include "rigel/renderer/texture.hpp"
#include "rigel/ui/bonus_screen.hpp"
#include "rigel/ui/duke_3d_teaser_screen.hpp"

#include <variant>
#include <vector>


namespace Rigel {
namespace ui {
class EpisodeEndScreen {
public:
	EpisodeEndScreen(GameMode::Context context, int episode);

	void updateAndRender(engine::TimeDelta dt);
	void handleEvent(const SDL_Event &event);

	bool finished() const;

private:
	std::vector<renderer::Texture> mScreenImages;
	std::size_t mCurrentImage = 0;
	IGameServiceProvider *mpServiceProvider;
};

class EpisodeEndSequence {
public:
	EpisodeEndSequence(
		GameMode::Context context,
		int episode,
		std::set<data::Bonus> achievedBonuses,
		int scoreWithoutBonuses);

	void updateAndRender(engine::TimeDelta dt);
	void handleEvent(const SDL_Event &event);

	bool finished() const;

private:
	template<typename T>
	void startNewStage(T &&newStage);

	struct InitialWait {
		engine::TimeDelta mElapsedTime = {};
	};
	#if 0
	using Stage = std::variant<
		InitialWait,
		ui::EpisodeEndScreen,
		ui::Duke3DTeaserScreen,
		ui::BonusScreen>;
	
	Stage mStage = InitialWait{};
#endif
	GameMode::Context mContext;
	std::set<data::Bonus> mAchievedBonuses;
	int mEpisode;
	int mScoreWithoutBonuses;
};

} // namespace ui
} // namespace Rigel
