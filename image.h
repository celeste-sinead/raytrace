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

#include "colour.h"
#include "ray.h"

class DisplayColour;
class ColourAdapter;
class QPaintEvent;

/*  Image data storage template, which provides functionality for
 *  storage of an image whose elements have (nearly) arbitrary type. 
 *  This should be the base of all image classes.
 *  Template type must define the assignment operator.
 *  As per convention in images, pixels are indexed such that 
 *  (0,0) is the top left pixel, x indices increase right, and y
 *  indices increase down */
template<typename PixT>
class ImageData {
protected:
    int      m_width;
    int      m_height;
    PixT   **m_pixels;
    
public:
    ImageData(int height = 0, int width = 0, PixT* fillColour = 0 );
    ImageData(const ImageData<PixT> & other);
    virtual ~ImageData();
 
    /** Image size access */
    int height() 
        { return m_height; }
    int width() 
        { return m_width; }
    /** Resize image.  Existing data is truncated, or padded, depending
     *  on size change.  If allocation fails, size will be set to 0x0 */
    void setSize(int height, int width, PixT *fillColour=0);
   
    /** Fill the image with a particular colour */
    void fill(PixT &fillColour);
   
    /** Access pixels. */
    PixT& at(int yInx, int xInx)
        { return m_pixels[yInx][xInx]; }
    PixT *operator[](int yInx)
        { return m_pixels[yInx]; }

private:
    /** Frees memory used to store the image */
    void freePix();
};

/** Template for images which have pixels of numeric type.
 *  This class provides basic image processing algorithms, and relies
 *  on the following operators being defined for the template type:
 *  - assignment, including assignment to '0'
 *  - subtraction (between PixT) and unary negation
 *  - multiplication and division (by PixT and by double) */
template<typename PixT>
class NumericImage : public ImageData<PixT> {
public:
    /** A filter kernel */
    typedef ImageData<PixT> Kernel;

public:
    NumericImage(int height = 0, int width = 0, PixT* fillColor = 0) :
        ImageData<PixT>(height, width, fillColor)
        {}
    NumericImage( const NumericImage<PixT> & other ) :
        ImageData<PixT>(other)
        {}

    /** Apply a given filter kernel to this image.
     *  @param filter  The kernel to apply.  Typically this will be square,
     *                 with odd width and height, but this is not a strict
     *                 requirement.  If width or height are even, then
     *                 the extra elements are considered to be right of / above
     *                 the kernel centre */
    void filter(Kernel &kernel);

    void resize(int newHeight, int newWidth);

    /** Fetch a pixel, allowing indices to go outside of bounds, with a zero
     *  slope boundary condition */
    PixT & framedGet(int yInx, int xInx);
};

/** An image containing traced rays */
class RayImage : public ImageData<Ray> {
public:
    RayImage(int height=0, int width=0, Ray* fillColour=0) :
        ImageData<Ray>(height,width,fillColour)
        { }
};

/** An image containing HDR ray colours */
class RayColourImage : public NumericImage<RayColour> {
public:
    RayColourImage(RayImage &ray);
};

/** An image composed of displayable colours */
class DisplayImage : public NumericImage<DisplayColour> {
public:
    DisplayImage(RayColourImage &ray, ColourAdapter &adapter);
};

/** A binary image rendered in text (for testing). i.e colours below
 *  a threshold are rendered as 'X' and others are rendered as a space */
class AsciiImage : public ImageData<char> {
public:
    AsciiImage(int height=0, int width=0, char *fill=0 ) :
        ImageData<char>(height,width,fill)
        { }
     
    /** Convert from a RayImage. 
     *  @param ray       The RayImage to convert from
     *  @param adapter   The colour adapter to use
     *  @param threshold The minimum DisplayColour intensity to consider
     *                   'bright'  (RGB are averaged to get intensity) */
    void fromRay( RayImage * ray, ColourAdapter * adapter, double threshold);
    
    //! Prints the ascii image to a file
    void print( FILE * outFile = stdout );
};

class DisplayImageQt : public QWidget { 
Q_OBJECT
private:
    QImage m_image;

protected:
    void paintEvent(QPaintEvent *event);

public:
    DisplayImageQt(DisplayImage &img, QWidget *parent = 0);

    virtual QSize sizeHint() const 
        { return m_image.size(); }
};

//! Include template function definitions
// inside_image_h_ is used to protect against inclusion elsewhere
#define inside_image_h_
#include "image.template.h"
#undef inside_image_h_

#endif //image_h_
