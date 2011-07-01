/******************************************************************************
 * render.h
 * Copyright 2011 Iain Peet
 *
 * A Render is a composite class containing all of the elements required to
 * render a scene.
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

#ifndef RENDER_H_
#define RENDER_H_

#include <tr1/memory>

class World;
class View;
class ImagePipeline;

/* Encapsulates a raytrace render.  
 * Currently, this is just a container - meat comes later */
class Render {
public:
  std::tr1::shared_ptr<World> m_world;
  std::tr1::shared_ptr<View>  m_view;
  std::tr1::shared_ptr<ImagePipeline> m_pipeline;

public:
  Render() : m_world(), m_view(), m_pipeline()
    { /* n/a */ }

};

#endif //RENDER_H_
