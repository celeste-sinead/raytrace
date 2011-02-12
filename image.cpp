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
#include <iputil/unit.h>

#include <QPaintEvent>
#include <QPainter>

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
    for( int y=0; y<height(); ++y) {
        for( int x=0; x<width(); ++x ) {
            fprintf(outFile,"%c",at(x,y)); 
        }
        fprintf(outFile,"\n");
    }
}

DisplayImageQt::DisplayImageQt(int width, int height, const QColor &fill, QWidget * parent) :
    QWidget(parent),
    m_image(width, height, QImage::Format_ARGB32)
{ 
    m_image.fill(fill.rgb());
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

}

void DisplayImageQt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), m_image);
}

void DisplayImageQt::fromRay(RayImage * ray, ColourAdapter * adapter)
{
    DisplayColour curC;
    QColor qCurC;
    for(int row=0; row < ray->height(); ++row) {
        for(int col=0; col < ray->width(); ++col) {
            adapter->convert(&(ray->at(col,row)), &curC);
            qCurC = QColor(curC.red(8), curC.green(8), curC.blue(8));
            m_image.setPixel(col, row, qCurC.rgb());
        }
    }
}

