/* Copyright (C) 2018, Nikolai Wuttke. All rights reserved.
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

#include <utility>
#include <variant>


namespace Rigel {
namespace base {
namespace detail {

//TODO:- applying a pack - expansion to a using - declaration requires at least '/std:c++17' 
#if 0
template<class... Ts>
struct overloaded : Ts... {
	using Ts::operator()...;
};
#endif

//TODO: fix C++17 deduction usage
#if 0
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
#endif

} // namespace detail

//TODO: fix C++17 std::visit usage
#if 0
template<typename Variant, typename... Matchers>
auto match(Variant &&variant, Matchers &&...matchers) {
	return std::visit(
		detail::overloaded{std::forward<Matchers>(matchers)...},
		std::forward<Variant>(variant));
}
#endif
} // namespace base
} // namespace Rigel
