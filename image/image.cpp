/******************************************************************************
* image.cpp
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

#include <cstdio>
#include <QPaintEvent>
#include <QPainter>

#include "image.h"

#include "util/trace.h"
#include "util/unit.h"
#include "rayImage.h"
#include "colour.h"

static trc_ctl_t imgTrace = {
    TRC_DFL_LVL,
    "IMAGE",
    TRC_STDOUT
};
#define TRACE(level, args...) \
    trc_printf(&imgTrace,level,1,args)

Image::Image(unsigned width, unsigned height, unsigned colours) :
    m_pixels(0), m_width(0), m_height(0), m_colours(0)
{
    resize(width, height, colours);
}

Image::~Image() {
    resize(0, 0, 0);
}

double** Image::allocPix(unsigned width, unsigned height, unsigned colours) {
    if(!(width && height && colours)) return 0;

    // Alloc array of pointers to images for each colour
    double **pix = new double* [colours];
    if (!pix) return 0;

    // Alloc image for each colour
    int i;
    bool failed=false;
    for(i=0; i<(int)(colours); ++i) {
        pix[i] = new double[width * height];
        if (!pix[i]) {
            failed = true;
            break;
        }
    }

    if (!failed) return pix;

    // Unwind on partial alloc fail.
    for(i=0; --i >= 0;) {
        delete [] pix[i];
    }
    delete pix;
    return 0;
}

void Image::freePix(double **pix, unsigned colours) {
    if (!pix) return;

    for(unsigned i=0; i<colours; ++i) {
        delete [] pix[i];
    }
    delete [] pix;
}

int Image::resize(unsigned width, unsigned height, unsigned colours) {
    if((width == m_width) && (height == m_height) && (colours == m_colours)) {
        return 0;
    }

    double **newPix = 0;
    if (width && height && colours) {
        newPix = allocPix(width, height, colours);
    }

    if (width && height && colours && (!newPix)) {
        // Alloc failed
        return -1;
    }

    freePix(m_pixels, m_colours);

    m_pixels = newPix;
    m_width = width;
    m_height = height;
    m_colours = colours;
    return 0;
}

Image& Image::swap(Image& other) {
    double **myPix = m_pixels;
    double myW = m_width;
    double myH = m_height;
    double myC = m_colours;

    m_pixels = other.m_pixels;
    m_width = other.m_width;
    m_height = other.m_height;
    m_colours = other.m_colours;

    other.m_pixels = myPix;
    other.m_width = myW;
    other.m_height = myH;
    other.m_colours = myC;

    return *this;
}

int Image::fromRay(const RayImage& ray) {
    if (resize(ray.width(), ray.height(), 3)) {
        return -1;
    }

    for(unsigned i=0; i<ray.height(); ++i) {
        for(unsigned j=0; j<ray.width(); ++j) {
            m_pixels[RED][i*m_width + j] = ray.at(i,j).m_colour.r;
            m_pixels[GREEN][i*m_width + j] = ray.at(i,j).m_colour.g;
            m_pixels[BLUE][i*m_width + j] = ray.at(i,j).m_colour.b;
        }
    }

    return 0;
}

