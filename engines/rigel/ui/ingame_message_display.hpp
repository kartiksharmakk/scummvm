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
#include "rigel/rigel.h"

#pragma once

#include <string>
#include <variant>

namespace Rigel
{
struct IGameServiceProvider;
}
namespace Rigel {
namespace ui {
class MenuElementRenderer;
}
} // namespace Rigel::ui

namespace Rigel {
namespace ui {

enum class MessagePriority {
	Normal,
	HintMachineMessage,
	Menu
};

class IngameMessageDisplay {
public:
	IngameMessageDisplay(
		IGameServiceProvider *pServiceProvider,
		MenuElementRenderer *pTextRenderer);

	void setMessage(
		std::string message,
		MessagePriority priority = MessagePriority::Normal);

	void update();
	void render();

private:
	// Multi-line messages are displayed line by line. The '*' character is used
	// as "line break" indicator. Each line is printed character by character,
	// then shown for the number of frames given by NEXT_LINE_DELAY. Afterwards,
	// either the next line starts printing, or the message disappears if already
	// finished.
	static constexpr auto NEXT_LINE_DELAY = 21;

	struct Idle {
	};

	struct Printing {
		Printing() = default;
		explicit Printing(const unsigned int offset)
			: mOffset(offset) {
		}

		unsigned int effectiveOffset() const { return mCharsPrinted + mOffset; }

		unsigned int mCharsPrinted = 0;
		unsigned int mOffset = 0;
	};

	struct Waiting {
		explicit Waiting(const unsigned int nextOffset)
			: mNextOffset(nextOffset) {
		}

		unsigned int mNextOffset = 0;
		unsigned int mFramesRemaining = NEXT_LINE_DELAY;
	};
	#if 0
	using State = std::variant<Idle, Printing, Waiting>;

	State mState;
	#endif
	std::string mMessage;
	std::string mPrintedMessage;
	MessagePriority mCurrentPriority = MessagePriority::Normal;

	MenuElementRenderer *mpTextRenderer;
	IGameServiceProvider *mpServiceProvider;
};

} // namespace ui
} // namespace Rigel
