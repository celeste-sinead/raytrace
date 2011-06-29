/******************************************************************************
* image.h
* Copyright 2010 Iain Peet
*
* Provides classes which store the colours of pixels in a rectangular image,
* as well as capabilites for converting between colour domains.
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

#ifndef image_h_
#define image_h_

#include <cstdio>
#include <vector>
#include <QColor>
#include <QImage>
#include <QObject>
#include <QWidget>

#include "trace/ray.h"
#include "colour.h"

class RayImage;

class Image {
private:
    double **m_pixels;
    unsigned m_width;
    unsigned m_height;
    unsigned m_colours;

private:
    double** allocPix(unsigned width, unsigned height, unsigned colours);
    void freePix(double **pix, unsigned colours);
    void copyPix(double **dst) const;

public:
    Image(unsigned width=0, unsigned height=0, unsigned colours=3);
    Image(const Image& other);
    Image& operator=(const Image& other);
    virtual ~Image();

    /* Resizes this image to the dimensions of the given RayImage and
     * copies the colours of the rays in the RayImage to this image's
     * pixels.
     * @return 0 on success, -1 on failure (allocation failure) */
    int fromRay(const RayImage& ray);

    /* Swap the contents of this image with another.
     * (Useful for not-in-place transforms, etc) 
     * @return a reference to this */
    Image& swap(Image &other);

    unsigned width() const {return m_width;}
    unsigned height() const {return m_height;}
    unsigned colours() const {return m_colours;}

    double& at(unsigned row, unsigned col, unsigned colour)
        {return m_pixels[colour][row*m_width + col];}
    double at(unsigned row, unsigned col, unsigned colour) const
        {return m_pixels[colour][row*m_width + col];}

    /* Resizes image.  If new alloc fails, size doesn't change.
     * @returns 0 on success, -1 on failed alloc */
    int resize(unsigned width, unsigned height, unsigned colours);
};

#endif //image_h_
