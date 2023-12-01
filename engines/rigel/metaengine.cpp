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

#include "common/translation.h"

#include "rigel/metaengine.h"
#include "rigel/detection.h"
#include "rigel/rigel.h"

namespace Rigel {

static const ADExtraGuiOptionsMap optionsList[] = {
	{
		GAMEOPTION_ORIGINAL_SAVELOAD,
		{
			_s("Use original save/load screens"),
			_s("Use the original save/load screens instead of the ScummVM ones"),
			"original_menus",
			false,
			0,
			0
		}
	},
	AD_EXTRA_GUI_OPTIONS_TERMINATOR
};

} // End of namespace Rigel

const char *RigelMetaEngine::getName() const {
	return "rigel";
}

const ADExtraGuiOptionsMap *RigelMetaEngine::getAdvancedExtraGuiOptions() const {
	return Rigel::optionsList;
}

Common::Error RigelMetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
	*engine = new Rigel::RigelEngine(syst, desc);
	return Common::kNoError;
}

bool RigelMetaEngine::hasFeature(MetaEngineFeature f) const {
	return checkExtendedSaves(f) ||
		(f == kSupportsLoadingDuringStartup);
}

#if PLUGIN_ENABLED_DYNAMIC(RIGEL)
REGISTER_PLUGIN_DYNAMIC(RIGEL, PLUGIN_TYPE_ENGINE, RigelMetaEngine);
#else
REGISTER_PLUGIN_STATIC(RIGEL, PLUGIN_TYPE_ENGINE, RigelMetaEngine);
#endif
