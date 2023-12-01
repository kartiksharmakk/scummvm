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

#include "base/plugins.h"
#include "common/config-manager.h"
#include "common/file.h"
#include "common/md5.h"
#include "common/str-array.h"
#include "common/translation.h"
#include "common/util.h"
#include "rigel/detection.h"
#include "rigel/detection_tables.h"

const DebugChannelDef RigelMetaEngineDetection::debugFlagList[] = {
	{ Rigel::kDebugGraphics, "Graphics", "Graphics debug level" },
	{ Rigel::kDebugPath, "Path", "Pathfinding debug level" },
	{ Rigel::kDebugFilePath, "FilePath", "File path debug level" },
	{ Rigel::kDebugScan, "Scan", "Scan for unrecognised games" },
	{ Rigel::kDebugScript, "Script", "Enable debug script dump" },
	DEBUG_CHANNEL_END
};

RigelMetaEngineDetection::RigelMetaEngineDetection() : AdvancedMetaEngineDetection(Rigel::gameDescriptions,
	sizeof(ADGameDescription), Rigel::rigelGames) {
}

REGISTER_PLUGIN_STATIC(RIGEL_DETECTION, PLUGIN_TYPE_ENGINE_DETECTION, RigelMetaEngineDetection);
