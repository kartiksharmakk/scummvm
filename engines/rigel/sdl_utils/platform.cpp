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



/* Copyright (C) 2021, Nikolai Wuttke. All rights reserved.
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

#include "rigel/sdl_utils/platform.hpp"


//TODO : sdl_video showing compilation errors
//#include <SDL_video.h>


//TODO: string_view only available in C++17
#if 0
#include <string_view>


namespace Rigel
{
	namespace sdl_utils{
bool isRunningInDesktopEnvironment()
{
  const auto sdlVideoDriver = std::string_view(SDL_GetCurrentVideoDriver());

  // clang-format off
  return
    sdlVideoDriver == "cocoa" ||
    sdlVideoDriver == "wayland" ||
    sdlVideoDriver == "windows" ||
    sdlVideoDriver == "x11";
  // clang-format on
}

}
} // namespace rigel::sdl_utils

#endif
