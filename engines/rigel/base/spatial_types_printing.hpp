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

#include "rigel/base/spatial_types.hpp"

#include <iomanip>
#include <iostream>


namespace Rigel {
namespace base {
template<typename ValueT>
std::ostream &operator<<(std::ostream &stream, const Vec2T<ValueT> &point) {
	stream << "Vec2{" << point.x << ", " << point.y << '}';
	return stream;
}

template<typename ValueT>
std::ostream &operator<<(std::ostream &stream, const Rect<ValueT> &rect) {
	stream << "Rect{" << rect.topLeft.x << ", " << rect.topLeft.y << ", "
		   << rect.size.width << ", " << rect.size.height << '}';
	return stream;
}

template<typename ValueT>
void outputFixedWidth(
	std::ostream &stream,
	const base::Vec2T<ValueT> &vec,
	const int width) {
	// clang-format off
  stream
    << std::setw(width) << std::fixed << std::setprecision(2) << vec.x << ", "
    << std::setw(width) << std::fixed << std::setprecision(2) << vec.y;
	// clang-format on
}

} // namespace base
} // namespace Rigel
