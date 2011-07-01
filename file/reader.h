/******************************************************************************
 * reader.h
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

#ifndef SCENE_READER_H_
#define SCENE_READER_H_

#include <json/reader.h>
#include <string>
#include <sstream>

#include "trace/render.h"

class SceneReader {
private:
  const char*  m_path;
  Json::Value  m_root;
  Json::Reader m_reader;

  bool m_valid;

  std::stringstream m_errStream;

  Render m_render;

private:
  /* Json::Value and Reader copy behaviour undocumented - disallow
   * for now, investigate if copying turns out to be necessary */
  SceneReader(const SceneReader& other);
  SceneReader& operator=(const SceneReader& other);

public:
  SceneReader(const char* path) :
    m_path(path), 
    m_root(), 
    m_reader(), 
    m_valid(false),
    m_errStream(),
    m_render()
    { /* n/a */ }

  /* Parse the file.
   * @return true if parsed successfully, false otherwise */
  bool parse();
  bool isValid() const {return m_valid;}

  /* Get the parsed render.  The internal state of the render
   * is undefined if this file is not valid. */
  Render& getRender();

  /* Get a string recording all errors that have occurred */
  std::string getErrors() const { return m_errStream.str(); }
};

#endif //SCENE_PARSER_H_
