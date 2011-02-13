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
#include <QColor>
#include <QImage>
#include <QObject>
#include <QWidget>

#include "colour.h"
#include "ray.h"

class DisplayColour;
class ColourAdapter;
class QPaintEvent;

/** Image base template, which provides data storage functionality
 *  to image classes 
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
    ImageData( int width = 0, int height = 0, PixT* fillColour = 0 );
    virtual ~ImageData();
 
    /** Image size access */
    int width() 
        { return m_width; }
    int height() 
        { return m_height; }
    /** Resize image.  Existing data is truncated, or padded, depending
     *  on size change.  If allocation fails, size will be set to 0x0 */
    void setSize(int width, int height, PixT *fillColour=0);
   
    /** Fill the image with a particular colour */
    void fill(PixT &fillColour);
   
    /** Access pixels */
    PixT& at(int xInx, int yInx)
        { return m_pixels[xInx][yInx]; }
    PixT *operator[](int xInx)
        { return m_pixels[xInx]; }

private:
    /** Frees memory used to store the image */
    void freePix();
};

/** An image containing traced rays */
class RayImage : public ImageData<Ray> {
public:
    RayImage( int width=0, int height=0, Ray* fillColour=0) :
        ImageData<Ray>(width,height,fillColour)
        { }

};

/** A binary image rendered in text (for testing). i.e colours below
 *  a threshold are rendered as 'X' and others are rendered as a space */
class AsciiImage : public ImageData<char> {
public:
    AsciiImage( int width=0, int height=0, char *fill=0 ) :
        ImageData<char>(width,height,fill)
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
    DisplayImageQt(int width=0, int height=0, const QColor &fill = Qt::black, QWidget *parent = 0);
    virtual QSize sizeHint() const { return m_image.size(); }

    /* Convert from a HDR RayImage
     * @param ray     The RayImage to convert from
     * @param adapter The colour converter to use */
    void fromRay(RayImage * ray, ColourAdapter * adapter);
};

//! Include template function definitions
// inside_image_h_ is used to protect against inclusion elsewhere
#define inside_image_h_
#include "image.template.h"
#undef inside_image_h_

#endif //image_h_
