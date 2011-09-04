/******************************************************************************
 * render.cpp
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

#include "trace/render.h"

#include "image/rayImage.h"
#include "trace/view.h"

using namespace std;

// Traces and processes a scene
auto_ptr<Image> Render::execute() {
    RayImage ri (m_renderSize);
    m_view->render(ri, *m_world, 20); 
    return m_pipeline->process(ri, m_processedSize);
}

