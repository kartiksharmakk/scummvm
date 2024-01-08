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

#include "rigel/data/movie.hpp"
#include "rigel/engine/timing.hpp"
#include "rigel/renderer/texture.hpp"

#include <functional>
#include "rigel/3party/tloptional/include/tl/optional.hpp"
#include <vector>


//add back renderer
namespace Rigel
{
namespace ui {
class MoviePlayer {
public:
	/** The frame callback will be invoked each time a new animation frame is
   * shown. If it returns a number, it will be used to set the new frame delay
   * for all subsequent frames.
   */

	
	using FrameCallbackFunc = std::function<tl::optional<int>(int)>;
	
	explicit MoviePlayer(renderer::Renderer *pRenderer);

	void playMovie(
		const data::Movie &movie,
		int frameDelayInFastTicks,

		//TODO fix C++17 std::nullopt usage 
		#if 0
		const tl::optional<int> &repetitions = std::nullopt,
		#endif
		
		FrameCallbackFunc frameCallback = nullptr
	
		
		);
	void updateAndRender(engine::TimeDelta timeDelta);
	bool hasCompletedPlayback() const;

private:
	struct FrameData {
		renderer::Texture mImage;
		int mStartRow;
	};

	void invokeFrameCallbackIfPresent(int whichFrame);

private:
	renderer::Renderer *mpRenderer;
	renderer::RenderTargetTexture mCanvas;
	std::vector<FrameData> mAnimationFrames;
	FrameCallbackFunc mFrameCallback = nullptr;
	
	bool mHasShownFirstFrame = false;
	int mCurrentFrame = 0;
	tl::optional<int> mRemainingRepetitions = 0;
	
	engine::TimeDelta mFrameDelay = 0.0;
	engine::TimeDelta mElapsedTime = 0.0;
};

} // namespace ui
} // namespace rigel::ui

