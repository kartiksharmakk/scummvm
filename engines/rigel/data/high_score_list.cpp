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


/* Copyright (C) 2019, Nikolai Wuttke. All rights reserved.
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

#include "rigel/data/high_score_list.hpp"

#include <algorithm>


namespace Rigel {
namespace data {
namespace {

template<typename Range>
auto findInsertionSpotForNewScore(const int score, Range &&list) {
	using namespace std;

	return find_if(begin(list), end(list), [score](const HighScoreEntry &entry) {
		return entry.mScore <= score;
	});
}

} // namespace

bool scoreQualifiesForHighScoreList(const int score, const HighScoreList &list) {
	return score > 0 &&
		   findInsertionSpotForNewScore(score, list) != std::end(list);
}

void insertNewScore(
	const int score,
	const std::string &name,
	HighScoreList &list) {
	using namespace std;

	auto it = findInsertionSpotForNewScore(score, list);
	if (it != end(list)) {
		rotate(it, prev(end(list)), end(list));
		*it = HighScoreEntry{name, score};
	}
}

} // namespace data
} // namespace Rigel
