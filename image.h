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

class RayColour;

/** An image containing pixels with raytracing colour domain colours 
 *  As per convention in images, pixels are indexed such that 
 *  (0,0) is the top left pixel, x indices increase right, and y
 *  indices increase down */
class RayImage {
private:
    int         m_width;
    int         m_height;
    RayColour **m_pixels;
    
public:
    RayImage( int width=0, int height=0, RayColour *fillColour=0);
    virtual ~RayImage()
        { freePix(); }
 
    /** Image size access */
    int width() 
        { return m_width; }
    int height() 
        { return m_height; }
    /** Resize image.  Existing data is truncated, or padded, depending
     *  on size change.  If allocation fails, size will be set to 0x0 */
    void setSize(int width, int height, RayColour *fillColour=0);
   
    /** Fill the image with a particular colour */
    void fill(RayColour &fillColour);
   
    /** Access pixels */
    RayColour *operator[](int xInx)
        { return m_pixels[xInx]; }
	
private:
    /** Frees memory used to store the image */
    void freePix();
};

#endif //image_h_
