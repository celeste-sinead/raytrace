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

#include <memory>
#include <tr1/memory>

#include "image/image.h"
#include "image/imageSize.h"
#include "image/pipeline.h"
#include "trace/view.h"
#include "trace/world.h"

/* Encapsulates a raytrace render. */
class Render {
public:
    std::tr1::shared_ptr<World>         m_world;
    std::tr1::shared_ptr<RayView>       m_view;
    std::tr1::shared_ptr<ImagePipeline> m_pipeline;
    // Max number of bounces for rendering
    int m_maxDepth;
    // Size of the image to actually trace
    ImageSize m_renderSize;
    // Size to interpolate to in postprocessing
    ImageSize m_processedSize;

public:
    Render() : 
        m_world(), 
        m_view(), 
        m_pipeline(), 
        m_maxDepth(0),
        m_renderSize(), 
        m_processedSize()
        { /* n/a */ }

    /* Execute the render.
     * @return the rendered image */
    std::auto_ptr<Image> execute();
};

#endif //RENDER_H_
