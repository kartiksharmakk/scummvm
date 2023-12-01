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

#include "rigel/data/duke_script.hpp"
#include "rigel/data/level_hints.hpp"

#include <string>
#include <unordered_map>


namespace Rigel {
namespace assets {

//TODO fix Script bundle usage of C++17 <variant>
#if 0
using ScriptBundle = std::unordered_map<std::string, data::script::Script>;

ScriptBundle loadScripts(const std::string &scriptSource);
#endif
data::LevelHints loadHintMessages(const std::string &scriptSource);


} // namespace assets
} // namespace Rigel
