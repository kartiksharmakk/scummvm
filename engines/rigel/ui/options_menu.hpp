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

#pragma once

#include "rigel/base/warnings.hpp"
#include "rigel/data/game_options.hpp"
#include "rigel/data/mod_library.hpp"
#include "rigel/engine/timing.hpp"

RIGEL_DISABLE_WARNINGS
#include <SDL_events.h>
//TODO fix imgui and imfilebrowser usage
#if 0
#include <imfilebrowser.h>
#include <imgui.h>
#endif
RIGEL_RESTORE_WARNINGS


namespace rigel
{
struct IGameServiceProvider;
class UserProfile;
} // namespace rigel

namespace Rigel
{
namespace renderer {
class Renderer;
}
} // namespace Rigel::

namespace Rigel {
namespace ui {
class OptionsMenu {
public:
	enum class Type {
		Main,
		InGame
	};

	OptionsMenu(
		UserProfile *pUserProfile,
		IGameServiceProvider *pServiceProvider,
		renderer::Renderer *pRenderer,
		Type type);
	~OptionsMenu();

	OptionsMenu(const OptionsMenu &) = delete;
	OptionsMenu &operator=(const OptionsMenu &) = delete;
	OptionsMenu(OptionsMenu &&) = default;
	OptionsMenu &operator=(OptionsMenu &&) = default;

	void handleEvent(const SDL_Event &event);
	void updateAndRender(engine::TimeDelta dt);
	bool isFinished() const;

private:
	void keyBindingRow(const char *label, SDL_Keycode *binding);
	void beginRebinding(SDL_Keycode *binding);
	void endRebinding();
	bool shouldDrawGamePathChooser() const;
	#if 0
	void drawGamePathChooser(const ImVec2 &sizeToUse);
	#endif
	void drawCreditsBox(engine::TimeDelta dt);

	#if 0
	ImGui::FileBrowser mGamePathBrowser;
	#endif
	UserProfile *mpUserProfile;
	data::GameOptions *mpOptions;
	IGameServiceProvider *mpServiceProvider;
	renderer::Renderer *mpRenderer;

	int mSelectedSoundIndex = 0;

	#if 0
	tl::optional<data::ModLibrary> moLocalModLibrary;
	#endif
	std::vector<data::ModStatus> mModSelection;
	bool mEnableTopLevelMods;

	SDL_Keycode *mpCurrentlyEditedBinding = nullptr;
	engine::TimeDelta mElapsedTimeEditingBinding = 0;
	engine::TimeDelta mElapsedTimeForCreditsBox = 0;
	float mGamePathChooserHeightNormalized = 0.0f;
	float mCreditsBoxContentHeightNormalized = 0.0f;

	Type mType;
	bool mMenuOpen = true;
	bool mPopupOpened = false;
	bool mShowErrorBox = false;
	bool mIsRunningInDesktopEnvironment;
};

} // namespace ui
} // namespace Rigel
