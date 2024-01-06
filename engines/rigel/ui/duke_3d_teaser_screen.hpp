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

/* Copyright (C) 2020, Nikolai Wuttke. All rights reserved.
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

#include "rigel/engine/timing.hpp"
#include "rigel/renderer/texture.hpp"

namespace Rigel {
namespace assets {
class ResourceLoader;
}
} // namespace Rigel
namespace Rigel {
namespace renderer {
class Renderer;
}
} // namespace Rigel::renderer

namespace Rigel {
namespace ui {
class Duke3DTeaserScreen {
public:
	Duke3DTeaserScreen(
		const assets::ResourceLoader &resources,
		renderer::Renderer *pRenderer);

	void updateAndRender(const engine::TimeDelta dt);
	bool isFinished() const;

private:
	renderer::Texture mTextImage;
	renderer::Renderer *mpRenderer;
	engine::TimeDelta mElapsedTime = 0.0;
};

} // namespace ui
} // namespace Rigel
