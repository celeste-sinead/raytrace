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

#include <cstdio>

#include <QPaintEvent>
#include <QPainter>

#include "image.h"
#include "colour.h"
#include "trace.h"
#include "unit.h"

static trc_ctl_t imgTrace = {
    TRC_DFL_LVL,
    "IMAGE",
    TRC_STDOUT
};
#define TRACE(level, args...) \
    trc_printf(&imgTrace,level,1,args)

RayColourImage::RayColourImage(RayImage & ray) :
    NumericImage<RayColour>(ray.height(), ray.width())
{
    for(int i=0; i<height(); ++i) {
        for(int j=0; j<width(); ++j) {
            at(i,j) = ray.at(i,j).m_colour;
        }
    }
}

DisplayImage::DisplayImage(RayColourImage &ray, ColourAdapter &adapter) :
    NumericImage<DisplayColour>(ray.height(), ray.width())
{
    for(int i=0; i<height(); ++i) {
        for(int j=0; j<width(); ++j) {
            adapter.convert(&(ray.at(i,j)), &at(i,j));
        }
    }
}

//! Converts a RayImage to Ascii
void AsciiImage::fromRay(RayImage* ray, ColourAdapter* adapter, double threshold)
{
    double intensity;
    for( int i=0; (i<ray->height()) && (i<height()); ++i ) {
        for( int j=0; (j<ray->width()) && (j<width()); ++j ) {
            RayColour & curC = ray->at(i,j).m_colour;
            intensity = curC.b + curC.g + curC.r;
            intensity /= 3.0;
            at(i,j) = (intensity>=threshold) ? ' ' : 'X';
        }
    }
}

//! Prints this image to a file
void AsciiImage::print(FILE* outFile)
{
    for( int y=0; y<height(); ++y) {
        for( int x=0; x<width(); ++x ) {
            fprintf(outFile,"%c",at(y,x)); 
        }
        fprintf(outFile,"\n");
    }
}

DisplayImageQt::DisplayImageQt(DisplayImage &img, QWidget * parent) :
    QWidget(parent),
    m_image(img.width(), img.height(), QImage::Format_ARGB32)
{ 
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    TRACE(TRC_INFO, "Created new DisplayImageQt, %dx%d\n", 
        m_image.width(), m_image.height());
    QColor curC;
    for(int i=0; i<img.height(); ++i) {
        for(int j=0; j<img.width(); ++j) {
            curC = QColor(img.at(i,j).red(8),
                           img.at(i,j).green(8),
                           img.at(i,j).blue(8));
            m_image.setPixel(j, i, curC.rgb());
        }
    }
}

void DisplayImageQt::paintEvent(QPaintEvent *event)
{
    TRACE(TRC_DTL, "Painted DisplayImageQt\n");
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), m_image);
}

