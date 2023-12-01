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

#include "rigel/audio/adlib_emulator.hpp"
#include "rigel/data/song.hpp"

#include <atomic>
#include <mutex>


namespace Rigel {
namespace audio {
class SoftwareImfPlayer {
public:
	explicit SoftwareImfPlayer(int sampleRate);
	SoftwareImfPlayer(const SoftwareImfPlayer &) = delete;
	SoftwareImfPlayer &operator=(const SoftwareImfPlayer &) = delete;

	#if 0
	void setType(AdlibEmulator::Type type);
	#endif

	void playSong(data::Song &&song);
	void setVolume(const float volume);

	void render(std::int16_t *pBuffer, std::size_t samplesRequired);

private:
	#if 0
	AdlibEmulator mEmulator;
	#endif
	std::mutex mAudioLock;
	data::Song mNextSongData;

	data::Song mSongData;
	data::Song::const_iterator miNextCommand;
	std::size_t mSamplesAvailable = 0;
	int mSampleRate;

	std::atomic<float> mVolume;
	std::atomic<bool> mSongSwitchPending;
	#if 0
	std::atomic<AdlibEmulator::Type> mTypeToUse;
	#endif
};

} // namespace audio
} // namespace Rigel
