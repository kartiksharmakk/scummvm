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

#include <cstddef>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

//TODO stringview and filesystem
#if 0
namespace Rigel
{
namespace assets {

class CMPFilePackage {
public:
	explicit CMPFilePackage(const std::filesystem::path &filePath);

	ByteBuffer file(std::string name) const;

	bool hasFile(std::string name) const;

private:
	struct DictEntry {
		DictEntry(std::uint32_t fileOffset, std::uint32_t fileSize);
		DictEntry(const DictEntry &) = default;
		DictEntry(DictEntry &&) = default;

		const std::uint32_t fileOffset = 0;
		const std::uint32_t fileSize = 0;
	};

	using FileDict = std::unordered_map<std::string, DictEntry>;

	FileDict::const_iterator findFileEntry(std::string name) const;

private:
	std::vector<std::uint8_t> mFileData;
	FileDict mFileDict;
};

} // namespace assets
} // namespace rigel::assets
#endif
