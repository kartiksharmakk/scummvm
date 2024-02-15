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

#ifndef CHAMBER_hga_H
#define CHAMBER_hga_H

namespace Chamber {

#define HGA_WIDTH 720
#define HGA_HEIGHT 348
#define HGA_BASE_SEG 0xB000
#define HGA_PAGE2_SEG 0xB800
#define HGA_NEXT_LINES_OFS 0x2000
#define HGA_BITS_PER_PIXEL 1
#define HGA_PIXELS_PER_BYTE (8 / HGA_BITS_PER_PIXEL)
#define HGA_BYTES_PER_LINE (HGA_WIDTH / HGA_PIXELS_PER_BYTE)
#define HGA_CALCXY_RAW(x, y) (((y) % 4) * HGA_NEXT_LINES_OFS + ((y) / 4) * HGA_BYTES_PER_LINE + (x) / HGA_PIXELS_PER_BYTE)
#define HGA_CENTERED_BASE_OFS HGA_CALCXY_RAW(32, 76)
// #ifdef __386__
// #define HGA_SCREENBUFFER ((byte*)(HGA_BASE_SEG * 16))
// #define HGA_cga_backbuffer ((byte*)(HGA_PAGE2_SEG * 16))
// #else
// #define HGA_SCREENBUFFER HGA_BASE_SEG
// #define HGA_cga_backbuffer HGA_PAGE2_SEG
// #endif
#define HGA_FONT_HEIGHT 6
// #define hgafrontbuffer HGA_SCREENBUFFER
// #define hgacga_backbuffer HGA_cga_backbuffer

uint16 hga_CalcXY(uint16 x, uint16 y);
uint16 hga_CalcXY_p(uint16 x, uint16 y);

} // End of namespace Chamber

#endif
