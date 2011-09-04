/******************************************************************************
 * rayImage.h
 * Copyright 2011 Iain Peet
 *
 * Provides RayImage, which is a rather abstract form of image where each pixel
 * is a traced ray.
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

#ifndef RAY_IMAGE_H_
#define RAY_IMAGE_H_ 

#include "trace/ray.h"

class ImageSize;

class RayImage {
private:
    // Rays.  All rows are concatenated into one array.
    Ray*     m_rays;
    unsigned m_width;
    unsigned m_height;

private:
    /* Disable, because Ray isn't copyable */
    RayImage(const RayImage &other);
    RayImage& operator=(const RayImage &other);

public:
    RayImage(unsigned width=0, unsigned height=0);
    RayImage(const ImageSize &size);
    virtual ~RayImage();

    unsigned width() const {return m_width;}
    unsigned height() const {return m_height;}

    Ray& at(unsigned row, unsigned col) 
        {return m_rays[row*m_width + col];}
    const Ray& at(unsigned row, unsigned col) const
        {return m_rays[row*m_width + col];}

    /* Resize.  This destroys preexisting data.
     * If new alloc fails, size doesn't change
     * @return 0 on success, -1 on fail */
    int setSize(unsigned width, unsigned height);
};

#endif //RAY_IMAGE_H_
