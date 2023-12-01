
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

#pragma once

#include "rigel/data/game_traits.hpp"
#include "rigel/engine/isprite_factory.hpp"
#include "rigel/renderer/texture_atlas.hpp"

#include <unordered_map>
#include <vector>


namespace Rigel {
namespace assets {
class ResourceLoader;
}
} // namespace Rigel::assets

namespace Rigel
{
namespace renderer {
class Renderer;
}
}

namespace Rigel {
namespace engine {
// The game draws player projectiles after drawing all regular actors, which
// makes them appear on top of everything. But in our case, they are rendered
// using the same mechanism as the other sprites, so we have to explicitly
// assign an order (which is higher than all regular actors' draw order).
constexpr auto PLAYER_PROJECTILE_DRAW_ORDER =
	data::GameTraits::maxDrawOrder + 1;
constexpr auto MUZZLE_FLASH_DRAW_ORDER = PLAYER_PROJECTILE_DRAW_ORDER + 1;
constexpr auto EFFECT_DRAW_ORDER = MUZZLE_FLASH_DRAW_ORDER + 1;

bool hasAssociatedSprite(data::ActorID actorID);
std::vector<int> buildImageIdTable(const assets::ResourceLoader &resources);

class SpriteFactory : public ISpriteFactory {
public:
	SpriteFactory(
		renderer::Renderer *pRenderer,
		const assets::ResourceLoader *pResourceLoader);

	engine::components::Sprite createSprite(data::ActorID id) override;
	base::Rect<int> actorFrameRect(data::ActorID id, int frame) const override;
	SpriteFrame actorFrameData(data::ActorID id, int frame) const override;

	bool hasHighResReplacements() const { return mHasHighResReplacements; }

	const renderer::TextureAtlas &textureAtlas() const {
		return mSpritesTextureAtlas;
	}

private:
	struct SpriteData {
		engine::SpriteDrawData mDrawData;
		std::vector<int> mInitialFramesToRender;
	};

	using CtorArgs = std::tuple<
		std::unordered_map<data::ActorID, SpriteData>,
		renderer::TextureAtlas,
		bool>;

	SpriteFactory(CtorArgs args);
	static CtorArgs construct(
		renderer::Renderer *pRenderer,
		const assets::ResourceLoader *pResourceLoader);

	std::unordered_map<data::ActorID, SpriteData> mSpriteDataMap;
	renderer::TextureAtlas mSpritesTextureAtlas;
	bool mHasHighResReplacements;
};

} // namespace engine
} // namespace Rigel
