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

/* Copyright (C) 2022, Nikolai Wuttke. All rights reserved.
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

#include "rigel/renderer/custom_quad_batch.hpp"
#include "rigel/renderer/shader.hpp"
#include "rigel/renderer/texture.hpp"


namespace Rigel {
namespace data {
struct GameOptions;
}
} // namespace Rigel

namespace Rigel {
namespace renderer {
class Renderer;
}
} // namespace Rigel


namespace Rigel {
namespace engine {
struct WaterEffectArea {
	base::Rect<int> mArea;
	bool mIsAnimated;
};

class SpecialEffectsRenderer {
public:
	SpecialEffectsRenderer(
		renderer::Renderer *pRenderer,
		const data::GameOptions &options);

	void rebuildBackgroundBuffer(const data::GameOptions &options);
	[[nodiscard]] auto bindBackgroundBuffer() { return mBackgroundBuffer.bind(); }
	void drawBackgroundBuffer();

	
	void drawWaterEffect(
		base::ArrayView<WaterEffectArea> areas,
		int surfaceAnimationStep);
	
	void drawCloakEffect(
		renderer::TextureId textureId,
		const renderer::TexCoords &texCoords,
		const base::Rect<int> &destRect) const;

private:
	renderer::Renderer *mpRenderer;
	renderer::Shader mWaterEffectShader;
	renderer::Shader mCloakEffectShader;
	#if 0
	renderer::CustomQuadBatch mBatch;
	#endif
	renderer::RenderTargetTexture mBackgroundBuffer;
	mutable renderer::RenderTargetTexture mCloakEffectTempBuffer;
	renderer::Texture mWaterSurfaceAnimTexture;
	renderer::Texture mWaterEffectPaletteTexture;
	renderer::Texture mCloakBlendMapTexture;
	renderer::MonoTexture mRgbToPaletteIndexMap;
};

} // namespace engine
} // namespace Rigel
