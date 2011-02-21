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
ImageData<PixT>::ImageData(int height, int width, PixT *fillColour) :
    m_width(0),
    m_height(0),
    m_pixels(0)
{
    setSize(height, width);
    if(fillColour) fill(*fillColour);
}

template<typename PixT>
ImageData<PixT>::ImageData(const ImageData<PixT> & other) :
    m_width(0),
    m_height(0),
    m_pixels(0)
{
    setSize(other.height(), other.width());

    /* Deep copy the other image's data */
    for(int i=0; i<other.height(); ++i) {
        for(int j=0; j<other.width(); ++j) {
            m_pixels[i][j] = other.m_pixels[i][j];
        }
    }
}

template<typename PixT>
ImageData<PixT>::~ImageData() {
    freePix();  
}

//! Resize the image
template<typename PixT>
void ImageData<PixT>::setSize(int height, int width, PixT *fillColour) {
    if( !width || !height ) {
        freePix();
        return;
    }

    /* Allocate new outer array */
    PixT ** newPixels = new PixT* [height];
    if(!newPixels) {
        freePix();
        return;
    }
    
    /* Allocate columns */
    for(int i=0; i<height; ++i) {
        newPixels[i] = new PixT [width];
        if( !newPixels[i]) {
            /* Alloc failed.  Unroll and get out.*/
            while( --i >= 0 ) delete [] newPixels[i];
            delete newPixels;
            freePix();
            return;
        }
    }
    
    /* Copy old data / fill with background */
    for(int i=0; i<height; ++i) {
        for(int j=0; j<width; ++j) {
            if( (i<m_height) && (j<m_width) ) {
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
    m_height = height;
    m_width =  width;
}

//! Fill the image with a pretty colour
template<typename PixT>
void ImageData<PixT>::fill(PixT& fillColour)
{
    for(int i=0; i<m_height; ++i) {
        for(int j=0; j<m_width; ++j) {
            m_pixels[i][j] = fillColour;   
        }
    }
}

//! Frees all memory
template<typename PixT>
void ImageData<PixT>::freePix()
{
    if( m_pixels ) {
        for(int i=0; i<m_height; ++i) delete [] m_pixels[i];
        delete [] m_pixels;
    }
    
    m_pixels = 0;
    m_width = 0;
    m_height = 0;
}

//! Get a pixel, with zero slope boundary condition
template<typename PixT>
PixT& NumericImage<PixT>::framedGet(int yInx, int xInx)
{
    /* Apply boundary condition - */
    if(yInx<0) yInx = 0;
    if(yInx>=ImageData<PixT>::height()) {
        yInx = ImageData<PixT>::height() - 1;
    }
    if(xInx<0) xInx = 0;
    if(xInx>=ImageData<PixT>::width()) {
        xInx = ImageData<PixT>::width() - 1;
    }

    PixT &temp = ImageData<PixT>::at(yInx, xInx);
    if(!&temp) {
        fprintf(stderr, "Null!\n");
    }
    return temp;
}

//! Apply a filter to an image
template<typename PixT>
void NumericImage<PixT>::filter(NumericImage<PixT>::Kernel &kernel)
{
    /* We cannot filter in place, so we need to create a new image
     * to write to */
    NumericImage<PixT> filtered(ImageData<PixT>::height(), ImageData<PixT>::width());

    /* Apply filter */
    for(int i=0; i<ImageData<PixT>::height(); ++i) {
        for(int j=0; j<ImageData<PixT>::width(); ++j) {
            // i and j are iterating through pixels in the image
            PixT filteredPix;
            filteredPix = 0.0;

            for(int n=0; n<kernel.height(); ++n) {
                for(int m=0; m<kernel.width(); ++m) {
                    PixT & temp = framedGet(
                            i + n - (kernel.height()/2),
                            j + m - (kernel.width()/2) );
                    filteredPix = filteredPix + 
                        kernel.at(n,m) * temp;
                }
            }

            filtered[i][j] = filteredPix;
        }
    }

    /* Rather than paying the expense of a copy, we just swap the data */
    PixT ** temp = ImageData<PixT>::m_pixels;
    ImageData<PixT>::m_pixels = filtered.m_pixels;
    filtered.m_pixels = temp;
}

//! Resize an image
template<typename PixT>
void NumericImage<PixT>::resize(int newHeight, int newWidth)
{
    
}

