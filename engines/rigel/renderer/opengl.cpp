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

#include "rigel/renderer/opengl.hpp"
#include "rigel/sdl_utils/error.hpp"

RIGEL_DISABLE_WARNINGS
#include <SDL_video.h>
RIGEL_RESTORE_WARNINGS

#include <stdexcept>

//TODO: fix gladLoadGLLoader usage
#if 0
void Rigel::renderer::loadGlFunctions()
{
  int result = 0;

  // clang-format off
#ifdef RIGEL_USE_GL_ES
  result = gladLoadGLES2Loader([](const char* proc) {
    return sdl_utils::check(SDL_GL_GetProcAddress(proc));
  });
#else
  result = gladLoadGLLoader([](const char* proc) {
    return sdl_utils::check(SDL_GL_GetProcAddress(proc));
  });
#endif
  // clang-format on

  if (!result)
  {
    throw std::runtime_error("Failed to load OpenGL function pointers");
  }
}
#endif
