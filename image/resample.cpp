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

#include <cmath>

#include "resample.h"

#include "image.h"

// Resample according to nearest neighbor
Image& NearestNeighbor::apply(Image &img) {
  // Allocate new image for resampled data
  Image resampled (m_xPix, m_yPix, img.colours());

  if ((resampled.width() != m_xPix) || (resampled.height() != m_yPix)) {
    // Alloc failure!
    return img;
  }

  double xScale = (double)(img.width()) / m_xPix;
  double yScale = (double)(img.height()) / m_yPix;

  for (unsigned i=0; i < m_yPix; ++i) {
    for (unsigned j=0; j < m_xPix; ++j) {
      double srcI = yScale * i;
      double srcJ = xScale * j;
      for (unsigned k=0; k < resampled.colours(); ++k) {
        resampled.at(i, j, k) = img.at(srcI, srcJ, k);
      }
    }
  }

  // Swap resampled data for old data
  return img.swap(resampled);
}

// Resample with the bilinear transform
Image& BilinearInterpolator::apply(Image &img) {
  // Allocate new image for resampled datta
  Image resampled (m_xPix, m_yPix, img.colours());

  if ((resampled.width() != m_xPix) || (resampled.height() != m_yPix)) {
    // Alloc failure!
    return img;
  }

  double xScale = (double)(img.width()-1) / m_xPix;
  double yScale = (double)(img.height()-1) / m_yPix;

  for (unsigned i=0; i < m_yPix; ++i) {
    for (unsigned j=0; j < m_xPix; ++j) {
      /* Scale dest i and j coords to src i and j coords */
      double iInSrc = yScale * i;
      double jInSrc = xScale * j;

      doBilinearSample(img, resampled, iInSrc, jInSrc, i, j);
    }
  }

  // Swap resampled data for old data
  return img.swap(resampled);
}

// Samples a single point with bilinear transform.
void BilinearInterpolator::doBilinearSample(
    Image &src, Image &dst, double srcI, double srcJ, int dstI, int dstJ) 
{
  for (unsigned k=0; k < src.colours(); ++k) {
    if ((srcI == (int)(srcI)) && (srcJ == (int)(srcJ))) {
      /* If source and dest coords are exactly the same, no need
       * to average. */
      dst.at(dstI, dstJ, k) = src.at(srcI, srcJ, k);
      continue;
    }

    /* Values for four corners surrounding point: */
    double ul = src.at(srcI, srcJ, k);
    double ur = src.at(srcI, srcJ + 1.0, k);
    double ll = src.at(srcI + 1.0, srcJ, k);
    double lr = src.at(srcI + 1.0, srcJ + 1.0, k);

    /* Interpolate in x direction, along top and bottom edges */
    double top = ul + (ur - ul)*(srcJ - (int)(srcJ));
    double bottom = ll + (lr - ll)*(srcJ - (int)(srcJ));

    dst.at(dstI, dstJ, k) = top + (bottom-top)*(srcI - (int)(srcI));
  }
}

