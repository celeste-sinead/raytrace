/******************************************************************************
 * rayImage.h
 * Copyright 2011 Iain Peet
 *
 * Provides RayImage, which is a form of image where each pixel is a trace ray.
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

#include "rayImage.h"

RayImage::RayImage(unsigned width, unsigned height) :
    m_rays(0), m_width(0), m_height(0)
{
    setSize(width, height);
}

RayImage::~RayImage() {
    setSize(0, 0);
}

int RayImage::setSize(unsigned width, unsigned height) {
    /* Alloc new */
    Ray *newRays = 0;
    if (width && height) {
        newRays = new Ray[width*height];
    }

    /* Check alloc */
    if (width && height && (!newRays)) {
        // Failed to alloc
        return -1;
    }

    /* Replace old */
    delete [] m_rays;
    m_rays = newRays;
    m_width = width;
    m_height = height;
    return 0;
}

