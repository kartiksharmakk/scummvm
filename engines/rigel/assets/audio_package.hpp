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

#include "rigel/assets/byte_buffer.hpp"

#include <array>
#include <cstdint>


namespace Rigel {
namespace assets {
constexpr auto AUDIO_DICT_FILE = "AUDIOHED.MNI";
constexpr auto AUDIO_DATA_FILE = "AUDIOT.MNI";

struct AdlibSound {
	std::uint8_t mOctave = 0;
	std::array<std::uint8_t, 16> mInstrumentSettings;
	std::vector<std::uint8_t> mSoundData;
};

using AudioPackage = std::vector<AdlibSound>;

AudioPackage loadAdlibSoundData(
	const ByteBuffer &audioDictData,
	const ByteBuffer &bundledAudioData);

} // namespace assets
} // namespace Rigel
