/******************************************************************************
* image.template.h
* Copyright 2010 Iain Peet
*
* Implements template functions from image.h.  This is included by
* image.h, and should not be included elsewhere.
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

#ifndef inside_image_h_
#error 'image.template.h should only be included by image.h'
#endif

#include "image.h"  // So KDevelop can find declarations

template<typename PixT>
ImageData<PixT>::ImageData(int width, int height, PixT *fillColour) :
    m_width(0),
    m_height(0),
    m_pixels(0)
{
    setSize(width,height);
    if(fillColour) fill(*fillColour);
}

template<typename PixT>
ImageData<PixT>::~ImageData() {
    freePix();  
}

//! Resize the image
template<typename PixT>
void ImageData<PixT>::setSize(int width, int height, PixT *fillColour) {
    /* Allocate new outer array */
    PixT ** newPixels = new PixT* [width];
    if(!newPixels) {
	freePix();
	return;
    }
    
    /* Allocate columns */
    for(int i=0; i<width; ++i) {
	newPixels[i] = new PixT [height];
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
template<typename PixT>
void ImageData<PixT>::fill(PixT& fillColour)
{
    for(int i=0; i<m_width; ++i) {
	for(int j=0; j<m_height; ++j) {
	    m_pixels[i][j] = fillColour;   
	}
    }
}

//! Frees all memory
template<typename PixT>
void ImageData<PixT>::freePix()
{
    for(int i=0; i<m_width; ++i)
	delete [] m_pixels[i];
    
    m_width = 0;
    m_height = 0;
}
