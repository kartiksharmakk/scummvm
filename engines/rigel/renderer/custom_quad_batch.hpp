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

#include "rigel/base/static_vector.hpp"
#include "rigel/base/warnings.hpp"
#include "rigel/renderer/renderer_support.hpp"
#include "rigel/renderer/vertex_buffer_utils.hpp"

RIGEL_DISABLE_WARNINGS
#include "rigel/3party/glm/mat4x4.hpp"
RIGEL_RESTORE_WARNINGS

#include <vector>
//TODO: fix base/static_vector
#if 0
namespace Rigel {
namespace renderer {
class Renderer;
class Shader;

glm::mat4 computeTransformationMatrix(renderer::Renderer *pRenderer);

class CustomQuadBatch {
public:
	explicit CustomQuadBatch(const Shader *pShader)
		: mpShader(pShader) {
	}

	void preAllocateSpace(const int numQuads) {
		mVertices.reserve(numQuads * std::tuple_size<QuadVertices>::value);
	}

	void reset() {
		mVertices.clear();
		mTextures.clear();
	}

	void addTexture(const TextureId textureId) { mTextures.push_back(textureId); }

	void addQuad(const TexCoords &sourceRect, const base::Rect<int> &destRect) {
		const auto vertices = createTexturedQuadVertices(sourceRect, destRect);
		mVertices.insert(mVertices.end(), std::begin(vertices), std::end(vertices));
	}

	CustomQuadBatchData data() const { return {mTextures, mVertices, mpShader}; }

private:
	base::static_vector<TextureId, MAX_MULTI_TEXTURES> mTextures;
	std::vector<float> mVertices;
	const Shader *mpShader;
};

} // namespace renderer
} // namespace Rigel
#endif
