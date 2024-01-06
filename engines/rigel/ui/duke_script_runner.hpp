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

#include "rigel/assets/palette.hpp"
#include "rigel/data/actor_ids.hpp"
#include "rigel/data/duke_script.hpp"
#include "rigel/data/saved_game.hpp"
#include "rigel/engine/tiled_texture.hpp"
#include "rigel/engine/timing.hpp"
#include "rigel/frontend/game_mode.hpp"
#include "rigel/renderer/texture.hpp"
#include "rigel/ui/menu_element_renderer.hpp"
#include "rigel/ui/menu_navigation.hpp"

#include <cstddef>
#include "rigel/3party/tloptional/include/tl/optional.hpp"


namespace Rigel {
namespace ui {
class DukeScriptRunner {
public:
	enum class ScriptTerminationType {
		RanToCompletion,
		AbortedByUser,
		MenuItemSelected,
		TimedOut
	};

	struct ExecutionResult {
		ScriptTerminationType mTerminationType;
		#if 0
		tl::optional<int> mSelectedPage;
		#endif
	};

	DukeScriptRunner(
		assets::ResourceLoader *pResourceLoader,
		renderer::Renderer *pRenderer,
		#if 0
		const data::SaveSlotArray *pSaveSlots,
		#endif
		IGameServiceProvider *pServiceProvider);

	#if 0
	void executeScript(const data::script::Script &script);
	#endif
	/** Clear canvas to transparent
   *
   * Allows starting off with a transparent canvas, in order to make it possible
   * to overlay script-based content on another image - e.g. when hitting
   * Escape while in-game, the "Confirm Quit" dialog box is shown on top of
   * the game.
   */
#include "rigel/rigel.h"
	void clearCanvas();

	bool hasFinishedExecution() const;
	#if 0
	tl::optional<ExecutionResult> result() const;
	#endif
	void updateAndRender(engine::TimeDelta dt);
	void handleEvent(const SDL_Event &event);

	#if 0
	tl::optional<int> currentPageIndex() const {
		return mPagerState ? std::make_optional(mPagerState->mCurrentPageIndex)
						   : std::nullopt;
	}
	#endif
private:
	enum class State {
		ReadyToExecute,
		ExecutingScript,
		AwaitingUserInput,
		AnimatingMessageBox,
		FinishedExecution,
		ExecutionInterrupted,
		ExecutionTimedOut,
	};

	struct DelayState {
		explicit DelayState(const int ticksToWait)
			: mTicksToWait(ticksToWait) {
		}

		int mTicksToWait;
		engine::TimeDelta mElapsedTime = 0;
	};

	struct NewsReporterState {
		explicit NewsReporterState(const int talkDuration)
			: mTalkDuration(talkDuration) {
		}

		int mTalkDuration;
		engine::TimeDelta mElapsedTime = 0;
	};

	struct MenuSelectionIndicatorState {
		explicit MenuSelectionIndicatorState(const int posY)
			: mPosY(posY) {
		}

		int mPosY;
		engine::TimeDelta mElapsedTime = 0;
	};

	enum PagingMode {
		Menu,
		PagingOnly
	};

	struct PagerState {
		#if 0
		std::vector<data::script::Script> mPageScripts;
		#endif
		PagingMode mMode;
		int mCurrentPageIndex;
		int mMaxPageIndex;
	};

	struct CheckBoxState {
		int mPosY;
		bool mChecked;
		data::script::SetupCheckBoxes::CheckBoxID mID;
	};

	struct CheckBoxesState {
		int mPosX;
		std::vector<CheckBoxState> mStates;
		int mCurrentMenuPosY;
	};

	struct MessageBoxState {
		engine::TimeDelta mElapsedTime;
		int mX;
		int mY;
		int mWidth;
		int mHeight;
		int mTextPosY;
	};

	#if 0
	void startExecution(const data::script::Script &script);
	#endif
	void interpretNextAction();

	bool isInWaitState() const;
	void clearWaitState();

	void drawSprite(data::ActorID id, int frame, int x, int y);
	void updatePalette(const data::Palette16 &palette);

	void drawSaveSlotNames(int selectedIndex);

	void drawCurrentKeyBindings();

	bool hasMenuPages() const;
	void selectNextPage(PagerState &state);
	void selectPreviousPage(PagerState &state);
	void confirmOrSelectNextPage(PagerState &state);
	void handleUnassignedButton(PagerState &state);
	void onPageChanged(PagerState &state);
	void executeCurrentPageScript(PagerState &state);
	void selectCurrentMenuItem(PagerState &state);
	void showMenuSelectionIndicator(int y);
	void hideMenuSelectionIndicator();

	void drawMenuSelectionIndicator(
		MenuSelectionIndicatorState &state,
		engine::TimeDelta dt);

	bool hasCheckBoxes() const;
	void displayCheckBoxes(const CheckBoxesState &state);

	void updateDelayState(DelayState &state, engine::TimeDelta timeDelta);
	void updateTimeoutToDemo(engine::TimeDelta timeDelta);
	void
	animateNewsReporter(NewsReporterState &state, engine::TimeDelta timeDelta);
	void stopNewsReporterAnimation();

	void updateAndRenderDynamicElements(engine::TimeDelta dt);
	void updateMessageBoxAnimation(engine::TimeDelta dt);

	#if 0
	void drawBigText(int x, int y, int colorIndex, std::string text) const;
	#endif
	void bindCanvas();
	void unbindCanvas();

private:
	const assets::ResourceLoader *mpResourceBundle;
	data::Palette16 mCurrentPalette;
	renderer::Renderer *mpRenderer;
	#if 0
	const data::SaveSlotArray *mpSaveSlots;
	#endif
	IGameServiceProvider *mpServices;
	engine::TiledTexture mUiSpriteSheetRenderer;
	MenuElementRenderer mMenuElementRenderer;

	renderer::RenderTargetTexture mCanvas;

	#if 0
	data::script::Script mCurrentInstructions;
	#endif
	std::size_t mProgramCounter;
	State mState = State::ReadyToExecute;

	#if 0
	tl::optional<DelayState> mDelayState;
	tl::optional<NewsReporterState> mNewsReporterAnimationState;

	tl::optional<PagerState> mPagerState;
	#endif
	bool mMenuItemWasSelected = false;
	
	std::unordered_map<int, int> mPersistentMenuSelections;
	#if 0
	tl::optional<MenuSelectionIndicatorState> mMenuSelectionIndicatorState;
	tl::optional<int> mCurrentPersistentSelectionSlot;

	tl::optional<CheckBoxesState> mCheckBoxStates;

	tl::optional<MessageBoxState> mMessageBoxState;

	tl::optional<engine::TimeDelta> mTimeSinceLastUserInput;
	#endif
	MenuNavigationHelper mNavigationHelper;

	bool mFadeInBeforeNextWaitStateScheduled = false;
	bool mDisableMenuFunctionalityForNextPagesDefinition = false;
	bool mTextBoxOffsetEnabled = false;
};

} // namespace ui
} // namespace Rigel
