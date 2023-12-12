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

#include "rigel/data/player_model.hpp"
#include "rigel/frontend/game_mode.hpp"
#include "rigel/ui/bonus_screen.hpp"
#include "rigel/ui/episode_end_sequence.hpp"

#include "rigel/frontend/game_runner.hpp"

#include <variant>

namespace Rigel {
namespace data {
struct SavedGame;
}

namespace rigel {

class GameSessionMode : public GameMode {
public:
	GameSessionMode(
		const data::GameSessionId &sessionId,
		Context context
		#if 0
		tl::optional<base::Vec2> playerPositionOverride = std::nullopt
	#endif
	);

	GameSessionMode(const data::SavedGame &save, Context context);

	#if 0
	std::unique_ptr<GameMode> updateAndRender(
		engine::TimeDelta dt,
		const std::vector<SDL_Event> &events) override;
#endif
	bool needsPerElementUpscaling() const override;

private:
	GameSessionMode(
		const data::GameSessionId &sessionId,
		data::PersistentPlayerState persistentPlayerState,
		Context context);

	void handleEvent(const SDL_Event &event);
	template<typename StageT>
	void fadeToNewStage(StageT &stage);
	void finishGameSession();
	#if 0
	void enterHighScore(std::string_view name);
	#endif

private:
	struct HighScoreNameEntry {
		ui::TextEntryWidget mNameEntryWidget;
	};

	struct HighScoreListDisplay {
	};

	#if 0
	using SessionStage = std::variant<
		std::unique_ptr<GameRunner>,
		ui::BonusScreen,
		ui::EpisodeEndSequence,
		HighScoreNameEntry,
		HighScoreListDisplay>;
	#endif
	data::PersistentPlayerState mPersistentPlayerState;
	#if 0
	SessionStage mCurrentStage;
	#endif
	const int mEpisode;
	int mCurrentLevelNr;
	const data::Difficulty mDifficulty;
	Context mContext;
};

} // namespace rigel
} // namespace Rigel
