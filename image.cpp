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

#include <iputil/unit.h>

#include "image.h"
#include "colour.h"

//! Converts a RayImage to Ascii
void AsciiImage::fromRay(RayImage* ray, ColourAdapter* adapter, double threshold)
{
    double intensity;
    for( int i=0; (i<ray->width()) && (i<width()); ++i ) {
        for( int j=0; (j<ray->height()) && (j<height()); ++j ) {
	    intensity = (ray->at(i,j)).b + (ray->at(i,j)).g + (ray->at(i,j)).r;
	    intensity /= 3.0;
	    at(i,j) = (intensity>=threshold) ? ' ' : 'X';
	}
    }
}

//! Prints this image to a file
void AsciiImage::print(FILE* outFile)
{
    
}
