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

#include "image.h"
#include "colour.h"

RayImage::RayImage(int width, int height, RayColour * fillColour) :
    m_width(0),
    m_height(0),
    m_pixels(0)
{
    setSize(width,height);
    if(fillColour) fill(*fillColour);
}

//! Resize the image
void RayImage::setSize(int width, int height, RayColour* fillColour) {
    /* Allocate new outer array */
    RayColour ** newPixels = new RayColour * [width];
    if(!newPixels) {
	freePix();
	return;
    }
    
    /* Allocate columns */
    for(int i=0; i<width; ++i) {
	newPixels[i] = new RayColour [height];
	if( !newPixels[i]) {
	    /* Alloc failed.  Unroll and get out.*/
	    while( --i >= 0 ) delete [] newPixels[i];
	    delete newPixels;
	    freePix();
	    return;
	}
    }
    
    /* Copy old data / fill with background */
    for(int i=0; i<width; ++i) {
	for(int j=0; j<height; ++j) {
	    if( (i<m_width) && (j<m_height) ) {
	        newPixels[i][j] = m_pixels[i][j];   
	    } else if( fillColour ) {
		newPixels[i][j] = *fillColour;
	    }
	}
    }
    
    // Free old data 
    freePix();
    // And add new data
    m_pixels = newPixels;
    m_width =  width;
    m_height = height;
}

//! Fill the image with a pretty colour
void RayImage::fill(RayColour& fillColour)
{
    for(int i=0; i<m_width; ++i) {
	for(int j=0; j<m_height; ++j) {
	    m_pixels[i][j] = fillColour;   
	}
    }
}

//! Frees all memory
void RayImage::freePix()
{
    for(int i=0; i<m_width; ++i)
	delete [] m_pixels[i];
    
    m_width = 0;
    m_height = 0;
}


