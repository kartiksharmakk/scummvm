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
#include "rigel/rigel.h"

#pragma once

#include "rigel/base/audio_buffer.hpp"
#include "rigel/base/defer.hpp"
#include "rigel/data/game_options.hpp"
#include "rigel/data/song.hpp"
#include "rigel/data/sound_ids.hpp"
#include "rigel/sdl_utils/ptr.hpp"

#include <array>
#include <memory>
#include <string>
#include <unordered_map>


namespace Rigel {
namespace assets {
class ResourceLoader;
}
} // namespace Rigel

namespace Rigel {
namespace audio {

using RawBuffer = std::vector<std::uint8_t>;

/** Provides sound and music playback functionality
 *
 * This class implements sound and music playback. When constructed, it opens
 * an audio device and loads all sound effects from the game's data files. From
 * that point on, sound effects and music playback can be triggered at any time
 * using the class' interface. Sound and music volume can also be adjusted.
 */
class SoundSystem {
public:
	explicit SoundSystem(
		const assets::ResourceLoader *pResources,
		data::SoundStyle soundStyle,
		data::AdlibPlaybackType adlibPlaybackType);
	~SoundSystem();

	void setSoundStyle(data::SoundStyle soundStyle);
	void setAdlibPlaybackType(data::AdlibPlaybackType adlibPlaybackType);

	/** Start playing given music data
   *
   * Starts playback of the song identified by the given name, and returns
   * immediately. Music plays in parallel to any sound effects.
   */
	void playSong(const std::string &name);

	/** Stop playing current song (if playing) */
	void stopMusic() const;

	/** Start playing specified sound effect
   *
   * Starts playback of the sound effect specified by the given sound ID, and
   * returns immediately. The sound effect will play in parallel to any other
   * currently playing sound effects, unless the same sound ID is already
   * playing. In the latter case, the already playing sound effect will be cut
   * off and playback will restart from the beginning.
   */
	void playSound(data::SoundId id) const;

	/** Stop playing specified sound effect (if currently playing) */
	void stopSound(data::SoundId id) const;
	void stopAllSounds() const;

	void setMusicVolume(float volume);
	void setSoundVolume(float volume);

private:
	void loadAllSounds(
		int sampleRate,
		std::uint16_t audioFormat,
		int numChannels,
		data::SoundStyle soundStyle);
	void reloadAllSounds();
	void applySoundVolume(float volume);
	void hookMusic() const;
	void unhookMusic() const;
	#if 0
	sdl_utils::Ptr<Mix_Music> loadReplacementSong(const std::string &name);
	#endif
	struct ImfPlayerWrapper;

	struct LoadedSound {
		LoadedSound() = default;
		explicit LoadedSound(RawBuffer buffer);
		#if 0
		explicit LoadedSound(sdl_utils::Ptr<Mix_Chunk> pMixChunk);
		#endif

		RawBuffer mData;
		#if 0
		sdl_utils::Ptr<Mix_Chunk> mpMixChunk;
		#endif
	};

	base::ScopeGuard mCloseMixerGuard;
	std::array<LoadedSound, data::NUM_SOUND_IDS> mSounds;
	std::unique_ptr<ImfPlayerWrapper> mpMusicPlayer;
	#if 0
	mutable sdl_utils::Ptr<Mix_Music> mpCurrentReplacementSong;
	#endif
	mutable std::unordered_map<std::string, std::string>
		mReplacementSongFileCache;
	const assets::ResourceLoader *mpResources;
	float mCurrentSoundVolume;
	data::SoundStyle mCurrentSoundStyle;
	data::AdlibPlaybackType mCurrentAdlibPlaybackType;
};

} // namespace audio
} // namespace Rigel
