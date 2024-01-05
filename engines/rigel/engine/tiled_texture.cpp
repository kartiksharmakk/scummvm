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

#include "rigel/engine/tiled_texture.hpp"

#include "rigel/data/game_traits.hpp"
#include "rigel/data/unit_conversions.hpp"
#include "rigel/renderer/vertex_buffer_utils.hpp"

#include <cassert>


namespace Rigel {
namespace engine {
using namespace data;
using namespace renderer;

TiledTexture::TiledTexture(Texture &&tileSet, Renderer *pRenderer)
	: mTileSetTexture(std::move(tileSet)), mpRenderer(pRenderer) {
}

TiledTexture::TiledTexture(
	Texture &&tileSet,
	const base::Size logicalSize,
	Renderer *pRenderer)
	: mTileSetTexture(std::move(tileSet)), mpRenderer(pRenderer), mScaleX(mTileSetTexture.width() / logicalSize.width), mScaleY(mTileSetTexture.height() / logicalSize.height) {
}

void TiledTexture::renderTileStretched(
	const int index,
	const base::Rect<int> &destRect) const {
	mTileSetTexture.render(sourceRect(index, 1, 1), destRect);
}

void TiledTexture::renderTile(const int index, const int x, const int y) const {
	renderTileGroup(index, x, y, 1, 1);
}
#if 0
renderer::QuadVertices TiledTexture::generateVertices(
	const int index,
	const int posX,
	const int posY) const {
	return renderer::createTexturedQuadVertices(
		renderer::toTexCoords(
			sourceRect(index, 1, 1),
			mTileSetTexture.width(),
			mTileSetTexture.height()),
		{tilesToPixels(base::Vec2{posX, posY}), tilesToPixels(base::Size{1, 1})});
}
#endif
void TiledTexture::renderTileSlice(
	const int baseIndex,
	const base::Vec2 &tlPosition) const {
	renderTileGroup(baseIndex, tlPosition.x, tlPosition.y, 1, 2);
}

void TiledTexture::renderTileQuad(
	const int baseIndex,
	const base::Vec2 &tlPosition) const {
	renderTileGroup(baseIndex, tlPosition.x, tlPosition.y, 2, 2);
}

void TiledTexture::renderTileDoubleQuad(
	const int baseIndex,
	const base::Vec2 &tlPosition) const {
	renderTileGroup(baseIndex, tlPosition.x, tlPosition.y, 4, 2);
}

void TiledTexture::renderTileAtPixelPos(int index, const base::Vec2 &pxPosition)
	const {
	mTileSetTexture.render(
		sourceRect(index, 1, 1), {pxPosition, tilesToPixels(base::Size{1, 1})});
}

int TiledTexture::tilesPerRow() const {
	return data::pixelsToTiles(mTileSetTexture.width() / mScaleX);
}

bool TiledTexture::isHighRes() const {
	return mScaleX > 1 || mScaleY > 1;
}

void TiledTexture::renderTileGroup(
	const int index,
	const int posX,
	const int posY,
	const int tileSpanX,
	const int tileSpanY) const {
	mpRenderer->drawTexture(
		mTileSetTexture.data(),
		renderer::toTexCoords(
			sourceRect(index, tileSpanX, tileSpanY),
			mTileSetTexture.width(),
			mTileSetTexture.height()),
		{tilesToPixels(base::Vec2{posX, posY}),
		 tilesToPixels(base::Size{tileSpanX, tileSpanY})});
}

base::Rect<int> TiledTexture::sourceRect(
	const int index,
	const int tileSpanX,
	const int tileSpanY) const {
	const base::Vec2 tileSetStartPosition{
		index % tilesPerRow(), index / tilesPerRow()};
	const auto topLeft = tilesToPixels(tileSetStartPosition);
	const auto size = tilesToPixels(base::Size{tileSpanX, tileSpanY});

	return {
		{topLeft.x * mScaleX, topLeft.y * mScaleY},
		{size.width * mScaleX, size.height * mScaleY}};
}

} // namespace engine
} // namespace Rigel
