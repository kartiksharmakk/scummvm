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

#include "rigel/base/defer.hpp"
#include "rigel/base/spatial_types.hpp"
#include "rigel/data/game_options.hpp"
#include "rigel/renderer/shader.hpp"
#include "rigel/renderer/texture.hpp"

#include <optional>

namespace Rigel
{
namespace data {
struct GameOptions;
}
} // namespace Rigel::

namespace Rigel {
namespace renderer {

class Renderer;

struct ViewportInfo {
	base::Vec2 mOffset;
	base::Size mSize;
	base::Vec2f mScale;
};

struct WidescreenViewportInfo {
	int mWidthTiles;
	int mWidthPx;
	int mLeftPaddingPx;
};

ViewportInfo determineViewport(const Renderer *pRenderer);

/** Returns true if wide-screen mode is feasible for the current window size.
 *
 * If the current window size has an aspect ratio that is less than 4:3, there
 * is no point in using wide-screen mode.
 */
bool canUseWidescreenMode(const Renderer *pRenderer);

bool canUsePixelPerfectScaling(
	const Renderer *pRenderer,
	const data::GameOptions &options);

WidescreenViewportInfo determineWidescreenViewport(const Renderer *pRenderer);

int determineLowResBufferWidth(
	const Renderer *pRenderer,
	const bool widescreenModeWanted);

RenderTargetTexture createFullscreenRenderTarget(
	Renderer *pRenderer,
	const data::GameOptions &options);

base::Vec2 offsetTo4by3WithinWidescreen(
	Renderer *pRenderer,
	const data::GameOptions &options);

class UpscalingBuffer {
public:
	UpscalingBuffer(Renderer *pRenderer, const data::GameOptions &options);

	[[nodiscard]] base::ScopeGuard bindAndClear(bool perElementUpscaling);
	void clear();
	void present(bool currentFrameIsWidescreen, bool perElementUpscaling);

	std::uint8_t alphaMod() const { return mAlphaMod; }

	void setAlphaMod(std::uint8_t alphaMod);
	void updateConfiguration(const data::GameOptions &options);

private:
	RenderTargetTexture mRenderTarget;
	#if 0
	Shader mSharpBilinearShader;
	#endif
	Renderer *mpRenderer;
	data::UpscalingFilter mFilter;
	bool mAspectRatioCorrection;
	std::uint8_t mAlphaMod = 0;
};

} // namespace renderer
} // namespace Rigel
