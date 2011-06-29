/******************************************************************************
 * resample.cpp
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

#include "resample.h"

#include "image.h"

// Resample according to nearest neighbor
Image& NearestNeighbor::apply(Image &img) {
  // Allocate new image for resampled data
  Image resampled (this->m_xPix, this->m_yPix, img.colours());

  if ((resampled.width() != m_xPix) || (resampled.height() != m_yPix)) {
    // Alloc failure!
    return img;
  }

  double xScale = (double)(img.width()) / this->m_xPix;
  double yScale = (double)(img.height()) / this->m_yPix;

  for (unsigned i=0; i < m_yPix; ++i) {
    for (unsigned j=0; j < m_xPix; ++j) {
      double srcI = yScale * i + 0.5;
      double srcJ = xScale * j + 0.5;
      for (unsigned k=0; k < resampled.colours(); ++k) {
        resampled.at(i, j, k) = img.at(srcI, srcJ, k);
      }
    }
  }

  // Swap resampled data for old data
  return img.swap(resampled);
}
