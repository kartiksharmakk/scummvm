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

#include "rigel/assets/palette.hpp"
#include "rigel/base/color.hpp"
#include "rigel/base/warnings.hpp"
#include "rigel/engine/tiled_texture.hpp"
#include "rigel/renderer/texture.hpp"

RIGEL_DISABLE_WARNINGS

//TODO Scummvm derivative to imgui
#if 0
#include <imgui.h>
#endif
RIGEL_RESTORE_WARNINGS

#include <string>


namespace Rigel
{
namespace assets {
class ResourceLoader;
}
} // namespace Rigel::assets


namespace Rigel {
namespace ui {

	//TODO fix imgui and string_view usage 
	#if 0
ImU32 toImgui(const base::Color &color);

renderer::Texture fullScreenImageAsTexture(
	renderer::Renderer *pRenderer,
	const assets::ResourceLoader &resources,
	std::string imageName);

engine::TiledTexture makeUiSpriteSheet(
	renderer::Renderer *pRenderer,
	const assets::ResourceLoader &resourceLoader,
	const data::Palette16 &palette);

void drawText(std::string text, int x, int y, const base::Color &color);

#endif
// TODO: There's probably a more appropriate place for this
void drawLoadingScreenText();

} // namespace ui
} // namespace Rigel
