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




/* Copyright (C) 2017, Nikolai Wuttke. All rights reserved.
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

#include <cstdint>
#include <cstdlib>

namespace Rigel
{
namespace base {
namespace detail {

[[noreturn]] void throwOutOfRange(std::uint32_t index);

}

/** Read-only array view type
 *
 * This has almost the same interface as std::array, but doesn't store the data
 * itself. Instead, it just holds a pointer plus the number of elements.
 * This allows creating lightweight views into arrays, which are cheap to copy
 * and store, but can be used like an array.
 *
 * Only allows read access.
 */
template<typename T>
class [[nodiscard]] ArrayView {
public:
	using value_type = T;
	using size_type = std::uint32_t;
	using difference_type = std::int32_t;
	using reference = value_type &;
	using const_reference = const value_type &;
	using pointer = value_type *;
	using const_pointer = const value_type *;
	using iterator = pointer;
	using const_iterator = const_pointer;

	constexpr ArrayView() = default;

	constexpr ArrayView(const_pointer pData, const size_type size) noexcept
		: mpData(pData),
		  mSize(size) {
	}

	// implicit on purpose
	template<std::size_t N>
	constexpr ArrayView(const value_type (&array)[N]) noexcept // NOLINT
		: mpData(array),
		  mSize(static_cast<size_type>(N)) {
	}

	// implicit on purpose
	template<typename Container>
	constexpr ArrayView(const Container &c) noexcept // NOLINT
		: mpData(c.data()),
		  mSize(static_cast<size_type>(c.size())) {
	}

	[[nodiscard]] constexpr const_iterator begin() const noexcept {
		return mpData;
	}

	[[nodiscard]] constexpr const_iterator end() const noexcept {
		return mpData + mSize;
	}

	[[nodiscard]] constexpr const_iterator cbegin() const noexcept {
		return mpData;
	}

	[[nodiscard]] constexpr const_iterator cend() const noexcept {
		return mpData + mSize;
	}

	[[nodiscard]] constexpr size_type size() const noexcept { return mSize; }

	[[nodiscard]] constexpr size_type max_size() const noexcept { return mSize; }

	[[nodiscard]] constexpr bool empty() const noexcept { return mSize == 0; }

	[[nodiscard]] constexpr const_reference
	operator[](const size_type index) const noexcept {
		return mpData[index];
	}

	[[nodiscard]] const_reference at(const size_type index) const {
		if (index >= mSize) {
			detail::throwOutOfRange(index);
		}

		return mpData[index];
	}

	[[nodiscard]] constexpr const_reference front() const noexcept {
		return mpData[0];
	}

	[[nodiscard]] constexpr const_reference back() const noexcept {
		return mpData[mSize - 1];
	}

	[[nodiscard]] constexpr const_pointer data() const noexcept { return mpData; }

private:
	const_pointer mpData = nullptr;
	size_type mSize = 0u;
};

/* Original code which used deduction guide c++17 feature , as a reference commented out.

template<typename Container>
ArrayView(Container) -> ArrayView<typename Container::value_type>;

*/

//In C++11, we cannot automatically deduce the template arguments when constructing a class template instance
//so i would need to explicitly use this makeArrayView function where required 
template<typename Container>
ArrayView<typename Container::value_type> makeArrayView(const Container &c) {
	return ArrayView<typename Container::value_type>(c.data(), c.size());
}




} // namespace base

} // namespace rigel::base

