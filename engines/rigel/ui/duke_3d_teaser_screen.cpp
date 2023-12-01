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

/* Copyright (C) 2020, Nikolai Wuttke. All rights reserved.
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

#include "rigel/ui/duke_3d_teaser_screen.hpp"

#include "rigel/assets/palette.hpp"
#include "rigel/assets/resource_loader.hpp"
#include "rigel/data/unit_conversions.hpp"
#include "rigel/renderer/renderer.hpp"


namespace Rigel {
namespace ui {
namespace {

constexpr auto TEXT_X_POS = data::tilesToPixels(5);
constexpr auto TEXT_Y_POS = 59;
constexpr auto TEXT_SLIDE_IN_START_OFFSET = 35;

constexpr auto TEXT_FADE_IN_TIME = engine::slowTicksToTime(64);
constexpr auto TEXT_SLIDE_IN_TIME =
	TEXT_FADE_IN_TIME + engine::slowTicksToTime(4);
constexpr auto TOTAL_DISPLAY_TIME =
	TEXT_SLIDE_IN_TIME + engine::slowTicksToTime(1500);

// clang-format off
constexpr data::Palette16 DUKE_3D_TEASER_TEXT_PALETTE{
  data::Pixel{  0, 0, 0, 255},
  data::Pixel{ 97, 0, 0, 255},
  data::Pixel{109, 0, 0, 255},
  data::Pixel{117, 0, 0, 255},
  data::Pixel{125, 0, 0, 255},
  data::Pixel{138, 0, 0, 255},
  data::Pixel{150, 0, 0, 255},
  data::Pixel{162, 0, 0, 255},
  data::Pixel{174, 0, 0, 255},
  data::Pixel{186, 0, 0, 255},
  data::Pixel{195, 0, 0, 255},
  data::Pixel{207, 0, 0, 255},
  data::Pixel{219, 0, 0, 255},
  data::Pixel{231, 0, 0, 255},
  data::Pixel{243, 0, 0, 255},
  data::Pixel{215, 0, 0, 255},
};
// clang-format on

auto loadImage(const assets::ResourceLoader &resources) {
	#if 0
	const auto actorData = resources.loadActor(
		data::ActorID::Duke_3d_teaser_text, DUKE_3D_TEASER_TEXT_PALETTE);
	return actorData.mFrames.at(0).mFrameImage;
	#endif
}

} // namespace



Duke3DTeaserScreen::Duke3DTeaserScreen(
	const assets::ResourceLoader &resources,
	renderer::Renderer *pRenderer){
	
	#if 0
	:
	mTextImage(pRenderer, loadImage(resources)), mpRenderer(pRenderer)
#endif

}

bool Duke3DTeaserScreen::isFinished() const {
	return mElapsedTime >= TOTAL_DISPLAY_TIME;
}

void Duke3DTeaserScreen::updateAndRender(const engine::TimeDelta dt) {
	mElapsedTime += dt;

	const auto alpha =
		255 * std::min(1.0f, float(mElapsedTime / TEXT_FADE_IN_TIME));
	const auto offset = TEXT_SLIDE_IN_START_OFFSET *
						(1.0f - std::min(1.0f, float(mElapsedTime / TEXT_SLIDE_IN_TIME)));

	const auto alphaRounded = base::roundTo<uint8_t>(alpha);

	const auto saved = renderer::saveState(mpRenderer);
	mpRenderer->setColorModulation({255, 255, 255, alphaRounded});
	mTextImage.render(TEXT_X_POS, TEXT_Y_POS + base::round(offset));
}

} // namespace ui
} // namespace Rigel
