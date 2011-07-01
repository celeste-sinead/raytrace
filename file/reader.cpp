/******************************************************************************
 * reader.cpp
 * Copyright 2011 Iain Peet
 *
 * Parses a json scene definition file, providing functions for generating 
 * World, View, and ImagePipeline objects from file.
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
#include <json/reader.h>

#include "reader.h"

using namespace std;

bool SceneReader::parse() {
	ifstream f (m_path, ios_base::in);
	if (f.fail()) {
		m_errStream << "Failed to open file";
		return false;
	}

	if (!m_reader.parse(f, m_root)) {
		m_errStream << "Failed to parse JSON:\n";
		m_errStream << m_reader.getFormattedErrorMessages();
		return false;
	}

	/* Check that required world and view objects exist */
	if (!m_root.isMember("world")) {
		m_errStream << "Missing required 'world' member";
		return false;
	}
	if (!m_root.isMember("view")) {
		m_errStream << "Missing required 'view' member";
		return false;
	}

	return true;
}

