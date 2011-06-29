/******************************************************************************
 * resample.h
 * Copyright 2011 Iain Peet
 *
 * Provides image transforms which resample images (typically, this is done
 * to resize the image)
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

#ifndef RESAMPLE_H_
#define RESAMPLE_H_

#include "image/transform.h"

class Image;

/* A simple nearest neighbor resampler.  Each resampled pixel takes on
 * the value of the nearest source pixel.  This is very fast, but not
 * particularly pretty */
class NearestNeighbor: public ImageTransform {
private:
  unsigned m_xPix;
  unsigned m_yPix;

public:
  NearestNeighbor(unsigned width, unsigned height) :
    m_xPix(width), m_yPix(height) 
    { /* nothing to do */ }

  virtual Image& apply(Image &img);
};

#endif //RESAMPLE_H_
