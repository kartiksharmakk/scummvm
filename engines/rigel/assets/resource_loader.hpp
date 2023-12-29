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

#pragma once

#define FORBIDDEN_SYMBOL_ALLOW_ALL

#include "common/path.h"
#include "common/debug.h"
#include "rigel/assets/actor_image_package.hpp"
#include "rigel/assets/cmp_file_package.hpp"
#include "rigel/assets/duke_script_loader.hpp"
#include "rigel/assets/palette.hpp"
#include "rigel/base/array_view.hpp"
#include "rigel/base/audio_buffer.hpp"
#include "rigel/base/image.hpp"
#include "rigel/data/movie.hpp"
#include "rigel/data/song.hpp"
#include "rigel/data/sound_ids.hpp"
#include "rigel/data/tile_attributes.hpp"

#include <string>
#include <vector>

namespace Rigel
{
namespace assets {
constexpr auto WIDE_HUD_WIDTH = 424;
constexpr auto WIDE_HUD_HEIGHT = 32;
constexpr auto WIDE_HUD_INNER_WIDTH = 368;

constexpr auto ULTRAWIDE_HUD_WIDTH = 560;
constexpr auto ULTRAWIDE_HUD_HEIGHT = 70;
constexpr auto ULTRAWIDE_HUD_INNER_WIDTH = 424;

struct TileSet {
	data::Image mTiles;
	data::map::TileAttributeDict mAttributes;
};

struct ActorData {
	struct Frame {
		base::Vec2 mDrawOffset;
		base::Size mLogicalSize;
		data::Image mFrameImage;
	};

	int mDrawIndex;
	std::vector<Frame> mFrames;
};


class ResourceLoader {
public:
	ResourceLoader(
		Common::Path gamePath,
		bool enableTopLevelMods,
		std::vector<Common::Path> modPaths);

	data::Image loadUiSpriteSheet() const;
	data::Image loadUiSpriteSheet(const data::Palette16 &overridePalette) const;

	data::Image loadStandaloneFullscreenImage(Common::String name) const;
	data::Palette16
	loadPaletteFromFullScreenImage(Common::String imageName) const;

	ActorData loadActor(
		data::ActorID id,
		const data::Palette16 &palette = data::GameTraits::INGAME_PALETTE) const;

	FontData loadFont() const { return mActorImagePackage.loadFont(); }

	int drawIndexFor(data::ActorID id) const {
		return mActorImagePackage.drawIndexFor(id);
	}

	int numActorFrames(data::ActorID id) const {
		return mActorImagePackage.numFramesFor(id);
	}

	data::Image loadAntiPiracyImage() const;

	data::Image loadWideHudFrameImage() const;
	data::Image loadUltrawideHudFrameImage() const;

	data::Image loadBackdrop(Common::String name) const;
	TileSet loadCZone(Common::String name) const;
	data::Movie loadMovie(Common::String name) const;

	data::Song loadMusic(Common::String name) const;
	bool hasSoundBlasterSound(data::SoundId id) const;
	base::AudioBuffer loadSoundBlasterSound(data::SoundId id) const;

	std::vector<Common::Path>
	replacementSoundPaths(data::SoundId id) const;
	std::vector<Common::Path> replacementMusicBasePaths() const;

	ScriptBundle loadScriptBundle(Common::String fileName) const;

	data::LevelHints loadHintMessages() const;

	ByteBuffer file(Common::String name) const;
	Common::String fileAsText(Common::String name) const;
	bool hasFile(Common::String name) const;

private:
	// The invoke_result of the TryLoadFunc is going to be a tl::optional<T>,
	// hence we need to unpack the underlying T via the optional's value_type

	/* original code for reference   C++17 std::invoke_result_t usage
	
	
	*/

	//TODO: fix std::invoke_result_t usage
	#if 0

	template<
		typename TryLoadFunc,
		//fix 
		typename T = typename std::
			invoke_result_t<TryLoadFunc, const Common::Path &>::value_type>
	tl::optional<T> tryLoadReplacement(TryLoadFunc &&tryLoad) const;

	/* a c++11 incomplete solution
	
	template<typename TryLoadFunc,
		typename T = typename std::result_of<TryLoadFunc(const Common::Path &)>::type>
	tl::optional<T> tryLoadReplacement(TryLoadFunc &&tryLoad) const;
	*/
	#endif

	tl::optional<data::Image>
	tryLoadPngReplacement(Common::String filename) const;
	
	data::Image loadEmbeddedImageAsset(
		const char *replacementName,
		base::ArrayView<std::uint8_t> data) const;
	
	data::Image loadTiledFullscreenImage(Common::String name) const;
	data::Image loadTiledFullscreenImage(
		Common::String name,
		const data::Palette16 &overridePalette) const;
	base::AudioBuffer loadSound(Common::String name) const;

	Common::Path mGamePath;
	std::vector<Common::Path> mModPaths;
	bool mEnableTopLevelMods;

	assets::CMPFilePackage mFilePackage;
	assets::ActorImagePackage mActorImagePackage;
};

} // namespace assets
} // namespace rigel::assets
