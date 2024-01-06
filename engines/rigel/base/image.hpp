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

#include "rigel/base/color.hpp"

#include <cstdint>
#include <vector>


namespace Rigel
{
namespace data {
	//:: is C++17 

using Pixel = Rigel::base::Color;

typedef Rigel::base::Color Pixel;
using PixelBuffer = std::vector<Pixel>;

/** Simple technology-agnostic image data holder.
 *
 * Always RGBA, 8-bit to keep things simple.
 */
#include "rigel/rigel.h"
class Image {
public:
	Image(PixelBuffer &&pixels, std::size_t width, std::size_t height);
	Image(const PixelBuffer &pixels, std::size_t width, std::size_t height);
	Image(std::size_t width, std::size_t height);

	const PixelBuffer &pixelData() const { return mPixels; }

	std::size_t width() const { return mWidth; }

	std::size_t height() const { return mHeight; }

	Image flipped() const;

	void insertImage(std::size_t x, std::size_t y, const Image &image);
	void insertImage(
		std::size_t x,
		std::size_t y,
		const PixelBuffer &pixels,
		std::size_t sourceWidth);

private:
	PixelBuffer mPixels;
	std::size_t mWidth;
	std::size_t mHeight;
};

} // namespace data
} // namespace rigel::data
