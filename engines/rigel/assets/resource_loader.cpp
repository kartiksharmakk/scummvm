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

#define FORBIDDEN_SYMBOL_ALLOW_ALL

#include "common/file.h"
#include "rigel/assets/resource_loader.hpp"

#include "rigel/assets/ega_image_decoder.hpp"
#include "rigel/assets/file_utils.hpp"
#include "rigel/assets/movie_loader.hpp"
#include "rigel/assets/music_loader.hpp"
#include "rigel/assets/png_image.hpp"
#include "rigel/assets/voc_decoder.hpp"
#include "rigel/base/container_utils.hpp"
#include "rigel/data/game_traits.hpp"
#include "rigel/data/unit_conversions.hpp"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <regex>


namespace Rigel {
namespace assets {
using namespace data;

namespace {

const auto ANTI_PIRACY_SCREEN_FILENAME = "LCR.MNI";

const auto FULL_SCREEN_IMAGE_DATA_SIZE =
	(GameTraits::viewportWidthPx * GameTraits::viewportHeightPx) /
	(GameTraits::pixelsPerEgaByte / GameTraits::egaPlanes);

// When loading assets, the game will first check if a file with an expected
// name exists at the replacements path, and if it does, it will load this file
// and use it instead of the asset from the original data file (NUKEM2.CMP).
//
// At the moment, this is implemented for sprites/actors, backdrops, and
// tilesets. The expected format for replacement files is:
//
//   backdrop<num>.png
//
//   tileset<num>.png
//
//   actor<actor_id>_frame<animation_frame>.png
//
// Where <num>, <actor_id> and <animation_frame> should be replaced with the
// corresponding numbers. For example, to replace the images used for the
// "blue guard" enemy, files named "actor159_frame0.png" up to
// "actor159_frame12.png" should be provided.
//
// For tilesets and backdrops, <num> should be the same number as in the
// original asset filename. E.g. to replace CZONE1.MNI, provide a file named
// tileset1.png, etc.
//
// The files can contain full 32-bit RGBA values, there are no limitations.
const auto ASSET_REPLACEMENTS_PATH = "asset_replacements";

Common::String replacementSpriteImageName(const int id, const int frame) {
	return "actor" + Common::String(id) + "_frame" + Common::String(frame) +
		   ".png";
}

tl::optional<data::Image> loadReplacementTilesetIfPresent(
	const Common::Path &resourcePath,
	Common::String name) {

	if (name.size() == 9 &&
		name.substr(0, 5) == "CZONE" &&
		name.substr(name.size() - 4) == ".MNI")

	{

		const Common::String number = name.substr(5, 1);

		const Common::String replacementName = "tileset" + number + ".png";
		const Common::Path replacementPath = resourcePath.join(replacementName, '/');

		return loadPng(replacementPath);
	} else {
		return {};

	}
}

int asSoundIndex(const data::SoundId id) {
	return static_cast<int>(id) + 1;
}

int asIntroSoundIndex(const data::SoundId id) {
	return static_cast<int>(id) - static_cast<int>(data::SoundId::IntroGunShot) +
		   3;
}

Common::String digitizedSoundFilenameForId(const data::SoundId soundId) {
	

	if (data::isIntroSound(soundId)) {
		return "INTRO" + Common::String(asIntroSoundIndex(soundId)) + ".MNI";
	}

	return "SB_" + Common::String(asSoundIndex(soundId)) + ".MNI";
}

#include "ultrawide_hud_image.ipp"
#include "wide_hud_image.ipp"

} // namespace

ResourceLoader::ResourceLoader(
	Common::Path gamePath,
	bool enableTopLevelMods,
	std::vector<Common::Path> modPaths)
	: mGamePath(std::move(gamePath)), mModPaths(std::move(modPaths)), mEnableTopLevelMods(enableTopLevelMods), mFilePackage(mGamePath.join("NUKEM2.CMP",'/')), mActorImagePackage(
																																						   file(ActorImagePackage::IMAGE_DATA_FILE),
																																						   file(ActorImagePackage::ACTOR_INFO_FILE)) {
}

//TODO: fix std::invoke_result_t usage in resource_loader.hpp
#if 0
template<typename TryLoadFunc, typename T>
tl::optional<T> ResourceLoader::tryLoadReplacement(TryLoadFunc &&tryLoad) const {
	for (auto iPath = mModPaths.rbegin(); iPath != mModPaths.rend(); ++iPath) {
		if (auto oReplacement = tryLoad(*iPath)) {
			return *oReplacement;
		}
	}

	if (mEnableTopLevelMods) {
		if (auto oReplacement = tryLoad(mGamePath / ASSET_REPLACEMENTS_PATH)) {
			return *oReplacement;
		}
	}

	return {};
}

tl::optional<data::Image>
ResourceLoader::tryLoadPngReplacement(Common::String filename) const {
	return tryLoadReplacement(
		[filename](const Common::Path &path) { return loadPng(path.join(filename,'/')); });
}
#endif

data::Image ResourceLoader::loadEmbeddedImageAsset(
	const char *replacementName,
	const base::ArrayView<std::uint8_t> data) const {
	if (const auto oReplacement = tryLoadPngReplacement(replacementName)) {
		return *oReplacement;
	}

	auto oEmbeddedImage = loadPng(data);
	if (!oEmbeddedImage) {
		throw std::runtime_error("Failed to decode embedded texture");
	}

	return *oEmbeddedImage;
}

data::Image ResourceLoader::loadUiSpriteSheet() const {
	const auto oReplacement = tryLoadPngReplacement("status.png");
	return oReplacement ? *oReplacement
						: loadUiSpriteSheet(data::GameTraits::INGAME_PALETTE);
}

data::Image ResourceLoader::loadUiSpriteSheet(
	const data::Palette16 &overridePalette) const {
	return loadTiledFullscreenImage("STATUS.MNI", overridePalette);
}

data::Image
ResourceLoader::loadTiledFullscreenImage(Common::String name) const {
	return loadTiledFullscreenImage(name, data::GameTraits::INGAME_PALETTE);
}

data::Image ResourceLoader::loadTiledFullscreenImage(
	Common::String name,
	const data::Palette16 &overridePalette) const {
	return loadTiledImage(
		file(name),
		data::GameTraits::viewportWidthTiles,
		overridePalette,
		data::TileImageType::Unmasked);
}

data::Image
ResourceLoader::loadStandaloneFullscreenImage(Common::String name) const {
	const auto &data = file(name);
	const auto paletteStart = data.begin() + FULL_SCREEN_IMAGE_DATA_SIZE;
	const auto palette = load6bitPalette16(paletteStart, data.end());

	auto pixels = decodeSimplePlanarEgaBuffer(
		data.begin(), data.begin() + FULL_SCREEN_IMAGE_DATA_SIZE, palette);
	return data::Image(
		std::move(pixels),
		GameTraits::viewportWidthPx,
		GameTraits::viewportHeightPx);
}

data::Image ResourceLoader::loadAntiPiracyImage() const {
	using namespace std;

	// For some reason, the anti-piracy screen is in a different format than all
	// the other full-screen images. It first defines a 256-color VGA palette,
	// then defines the pixel data in linear format.
	//
	// See http://www.shikadi.net/moddingwiki/Duke_Nukem_II_Full-screen_Images
	const auto &data = file(ANTI_PIRACY_SCREEN_FILENAME);
	const auto iImageStart = begin(data) + 256 * 3;
	const auto palette = load6bitPalette256(begin(data), iImageStart);

	data::PixelBuffer pixels;
	pixels.reserve(GameTraits::viewportWidthPx * GameTraits::viewportHeightPx);
	transform(
		iImageStart,
		end(data),
		back_inserter(pixels),
		[&palette](const auto indexedPixel) { return palette[indexedPixel]; });
	return data::Image(
		move(pixels), GameTraits::viewportWidthPx, GameTraits::viewportHeightPx);
}

data::Image ResourceLoader::loadWideHudFrameImage() const {
	return loadEmbeddedImageAsset("remixed_hud_1.png", WIDE_HUD_IMAGE);
}

data::Image ResourceLoader::loadUltrawideHudFrameImage() const {
	return loadEmbeddedImageAsset("remixed_hud_2.png", ULTRAWIDE_HUD_IMAGE);
}

data::Palette16 ResourceLoader::loadPaletteFromFullScreenImage(
	Common::String imageName) const {
	const auto &data = file(imageName);
	const auto paletteStart = data.begin() + FULL_SCREEN_IMAGE_DATA_SIZE;
	return load6bitPalette16(paletteStart, data.end());
}

#if 0
ActorData ResourceLoader::loadActor(
	data::ActorID id,
	const data::Palette16 &palette) const {
	const auto &actorInfo = mActorImagePackage.loadActorInfo(id);

	auto images = utils::transformed(
		actorInfo.mFrames, [&, frame = 0](const auto &frameHeader) mutable {
			const auto imageName =
				replacementSpriteImageName(static_cast<int>(id), frame);
			++frame;

			const auto oReplacement = tryLoadPngReplacement(imageName);
			return ActorData::Frame{
				frameHeader.mDrawOffset,
				frameHeader.mSizeInTiles,
				oReplacement ? *oReplacement
							 : mActorImagePackage.loadImage(frameHeader, palette)};
		});

	return ActorData{actorInfo.mDrawIndex, std::move(images)};
}
#endif

data::Image ResourceLoader::loadBackdrop(Common::String name) const {
	

	if (name.size() == 8 && name.substr(0, 4) == "DROP" &&
    name.substr(name.size() - 4) == ".MNI" ){

		const auto number = name.substr(4, 1);
		const auto replacementName = "backdrop" + number + ".png";

		if (const auto oReplacement = tryLoadPngReplacement(replacementName)) {
			return *oReplacement;
		}
	}

	return loadTiledFullscreenImage(name);
}
#if 0
TileSet ResourceLoader::loadCZone(Common::String name) const {
	using namespace data;
	using namespace map;
	using T = data::TileImageType;

	const auto &data = file(name);
	LeStreamReader attributeReader(
		data.begin(), data.begin() + GameTraits::CZone::attributeBytesTotal);
	std::vector<uint16_t> attributes;
	attributes.reserve(GameTraits::CZone::numTilesTotal);
	for (TileIndex index = 0; index < GameTraits::CZone::numTilesTotal; ++index) {
		attributes.push_back(attributeReader.readU16());

		if (index >= GameTraits::CZone::numSolidTiles) {
			attributeReader.skipBytes(sizeof(uint16_t) * 4);
		}
	}
	
	const auto oReplacementImage =
		tryLoadReplacement([name](const Common::Path &path) {
			return loadReplacementTilesetIfPresent(path, name);
		});

	if (oReplacementImage) {
		return {
			std::move(*oReplacementImage), TileAttributeDict{std::move(attributes)}};
	}
	
	Image fullImage(
		tilesToPixels(GameTraits::CZone::tileSetImageWidth),
		tilesToPixels(GameTraits::CZone::tileSetImageHeight));

	const auto tilesBegin = data.begin() + GameTraits::CZone::attributeBytesTotal;
	const auto maskedTilesBegin = tilesBegin +
								  GameTraits::CZone::numSolidTiles * GameTraits::CZone::tileBytes;

	const auto solidTilesImage = loadTiledImage(
		tilesBegin,
		maskedTilesBegin,
		GameTraits::CZone::tileSetImageWidth,
		data::GameTraits::INGAME_PALETTE,
		T::Unmasked);
	const auto maskedTilesImage = loadTiledImage(
		maskedTilesBegin,
		data.end(),
		GameTraits::CZone::tileSetImageWidth,
		data::GameTraits::INGAME_PALETTE,
		T::Masked);
	fullImage.insertImage(0, 0, solidTilesImage);
	fullImage.insertImage(
		0,
		tilesToPixels(GameTraits::CZone::solidTilesImageHeight),
		maskedTilesImage);

	return {std::move(fullImage), TileAttributeDict{std::move(attributes)}};
}
#endif
#if 0
data::Movie ResourceLoader::loadMovie(Common::String name) const {
	// We don't use tryLoadReplacement here, because we don't look for movies
	// in the top-level path.
	for (auto iPath = mModPaths.rbegin(); iPath != mModPaths.rend(); ++iPath) {
		const auto moddedFile = *iPath.join(name, '/');
		if (Common::File::exists(moddedFile)) {
			return assets::loadMovie(loadFile(moddedFile));
		}
	}

	return assets::loadMovie(loadFile(mGamePath.join(name,'/')));
}
#endif

data::Song ResourceLoader::loadMusic(Common::String name) const {
	return assets::loadSong(file(name));
}

bool ResourceLoader::hasSoundBlasterSound(const data::SoundId id) const {
	return hasFile(digitizedSoundFilenameForId(id));
}

base::AudioBuffer
ResourceLoader::loadSoundBlasterSound(const data::SoundId id) const {
	const auto digitizedSoundFileName = digitizedSoundFilenameForId(id);
	if (hasFile(digitizedSoundFileName)) {
		return loadSound(digitizedSoundFileName);
	}

	return {};
}

std::vector<Common::Path>
ResourceLoader::replacementSoundPaths(data::SoundId id) const {
	

	const Common::String expectedName = "sound" + Common::String(static_cast<int>(id) + 1) + ".wav";

	auto result = std::vector<Common::Path>{};
	result.reserve(mModPaths.size());

	std::transform(
		mModPaths.rbegin(),
		mModPaths.rend(),
		std::back_inserter(result),
		[&](const auto &path) { return path.join(expectedName,'/'); });


	//TODO : fix ASSET_REPLACEMENTS_PATH usage
	#if 0
	if (mEnableTopLevelMods) {
		result.push_back(mGamePath / ASSET_REPLACEMENTS_PATH / expectedName);
	}
	#endif

	return result;
}

std::vector<Common::Path>
ResourceLoader::replacementMusicBasePaths() const {
	auto result =
		std::vector<Common::Path>{mModPaths.rbegin(), mModPaths.rend()};

	//TODO : fix ASSET_REPLACEMENTS_PATH usage
	#if 0
	if (mEnableTopLevelMods) {
		result.push_back(mGamePath / ASSET_REPLACEMENTS_PATH);
	}
	#endif
	return result;
}

base::AudioBuffer ResourceLoader::loadSound(Common::String name) const {
	return assets::decodeVoc(file(name));
}


//TODO: fix asText in file_utils.cpp  from std::string to Common::String
#if 0
ScriptBundle ResourceLoader::loadScriptBundle(Common::String fileName) const {
	return assets::loadScripts(fileAsText(fileName));
}

data::LevelHints ResourceLoader::loadHintMessages() const {
	return assets::loadHintMessages(fileAsText("HELP.MNI"));
}

ByteBuffer ResourceLoader::file(Common::String name) const {
	// TODO: Eliminate duplication with tryLoadReplacement?
	for (auto iPath = mModPaths.rbegin(); iPath != mModPaths.rend(); ++iPath) {
		const auto unpackedFilePath = *iPath / Common::Path(name);
		if (Common::File::exists(unpackedFilePath)) {
			return loadFile(unpackedFilePath);
		}
	}

	if (mEnableTopLevelMods) {
		const auto unpackedFilePath = mGamePath / Common::Path(name);
		if (Common::File::exists(unpackedFilePath)) {
			return loadFile(unpackedFilePath);
		}
	}

	return mFilePackage.file(name);
}

Common::String ResourceLoader::fileAsText(Common::String name) const {
	return asText(file(name));
}

bool ResourceLoader::hasFile(Common::String name) const {
	// TODO: Eliminate duplication with tryLoadReplacement?
	for (auto iPath = mModPaths.rbegin(); iPath != mModPaths.rend(); ++iPath) {
		const auto unpackedFilePath = *iPath / Common::Path(name);
		if (Common::File::exists(unpackedFilePath)) {
			return true;
		}
	}

	if (mEnableTopLevelMods) {
		const auto unpackedFilePath = mGamePath / Common::Path(name);
		if (Common::File::exists(unpackedFilePath)) {
			return true;
		}
	}

	return mFilePackage.hasFile(name);
}
#endif
} // namespace assets
} // namespace Rigel
