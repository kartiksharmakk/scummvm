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
#include "rigel/rigel.h"

#pragma once

#include "rigel/base/warnings.hpp"
#include "rigel/engine/timing.hpp"

RIGEL_DISABLE_WARNINGS
#include <SDL.h>
RIGEL_RESTORE_WARNINGS

#include <string>


namespace Rigel {
namespace ui {
class MenuElementRenderer;

class TextEntryWidget {
public:
	enum class Style {
		Regular,
		BigText
	};

	// Position is given in tiles
	TextEntryWidget(
		const ui::MenuElementRenderer *pUiRenderer,
		int posX,
		int posY,
		int maxTextLength,
		Style textStyle
		#if 0
		std::string initialText = ""
		#endif

	);

	void handleEvent(const SDL_Event &event);
	void updateAndRender(engine::TimeDelta dt);
	#if 0
	std::string text() const;
	#endif
private:
	std::string mText;
	engine::TimeDelta mElapsedTime = 0.0;
	const ui::MenuElementRenderer *mpUiRenderer;
	int mPosX;
	int mPosY;
	int mMaxTextLength;
	Style mTextStyle;
};

} // namespace ui
} // namespace Rigel
