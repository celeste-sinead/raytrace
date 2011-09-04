/******************************************************************************
 * logger.cpp
 * Copyright 2011 Iain Peet
 *
 * Provides a simple logger class.
 ******************************************************************************
 * This program is distributed under the of the GNU Lesser Public License. 
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

#include <iostream>
#include <fstream>

#include "util/logger.h"

using namespace std;

static ostream& _getDevNull() {
	return cout;
}

ostream& Logger::operator()(enum LogLevel level) {
	if (level <= m_level) {
		return cout;
	} else {
		return _getDevNull();
	}
}

