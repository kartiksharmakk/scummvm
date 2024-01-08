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



#include "rigel/assets/byte_buffer.hpp"
#include "common/path.h"
#include "common/file.h"
#include "common/error.h"
#include <cstdint>
#include "rigel/3party/tloptional/include/tl/optional.hpp"


#include <string>


namespace Rigel
{
namespace assets {

tl::optional<ByteBuffer> tryLoadFile(const Common::Path &path);

/** Load entire contents of file with given name into ByteBuffer
 *
 * Throws an exception if the file can't be opened.
 */
ByteBuffer loadFile(const Common::Path &path);

/* Original code block for future reference

inline ByteBuffer loadFile(const std::string &fileName) {
	return loadFile(std::filesystem::u8path(fileName));
}
*/
inline ByteBuffer loadFile(const Common::String &fileName) {
	//TODO check if std::filesystem::u8path is proper replacement with Common::Path
	return loadFile(Common::Path(fileName));
}
void saveToFile(
	const assets::ByteBuffer &buffer,
	const Common::Path &filePath
	);

std::string asText(const ByteBuffer &buffer);

/** Offers checked reading of little-endian data from a byte buffer
 *
 * All readX() methods will throw if there is not enough data left.
 */
class LeStreamReader {
public:
	explicit LeStreamReader(const ByteBuffer &data);
	LeStreamReader(ByteBufferCIter begin, ByteBufferCIter end);

	std::uint8_t readU8();
	std::uint16_t readU16();
	/** Read 32bit little-endian word encoded as 3 bytes */
	std::uint32_t readU24();
	std::uint32_t readU32();

	std::int8_t readS8();
	std::int16_t readS16();
	/** Read 32bit little-endian word encoded as 3 bytes */
	std::int32_t readS24();
	std::int32_t readS32();

	std::uint8_t peekU8();
	std::uint16_t peekU16();
	std::uint32_t peekU24();
	std::uint32_t peekU32();

	std::int8_t peekS8();
	std::int16_t peekS16();
	std::int32_t peekS24();
	std::int32_t peekS32();

	void skipBytes(std::size_t count);
	bool hasData() const;
	ByteBufferCIter currentIter() const;

private:
	template<typename Callable>
	auto withPreservingCurrentIter(Callable func);

	ByteBufferCIter mCurrentByteIter;
	const ByteBufferCIter mDataEnd;
};

std::string readFixedSizeString(LeStreamReader &reader, std::size_t len);

} // namespace assets
} // namespace Rigel::
