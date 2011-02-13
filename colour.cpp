/******************************************************************************
 * colour.cpp
 * Copyright 2010 Iain Peet
 *
 * Implements colouring for raytracing.
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
#include <cstdlib>

#include "colour.h"
#include "ray.h"
#include "image.h"

//! Set all components of the colour
void RayColour::set(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

RayColour RayColour::operator*(const RayColour& other)
{
    return RayColour(r*other.r, g*other.g, b*other.b);
}
RayColour RayColour::operator*(double other)
{
    return RayColour(r*other, g*other, b*other);
}
RayColour operator*(double left, const RayColour & other)
{
    return RayColour(left*other.r, left*other.g, left*other.b);
}
RayColour RayColour::operator+(const RayColour& other)
{
    return RayColour(r+other.r, g+other.g, b+other.b);
}
RayColour RayColour::operator-(const RayColour& other)
{
    return RayColour(r-other.r, g-other.g, b-other.b);
}
double& RayColour::operator[](int inx) {
    switch(inx) {
        case 0: return r;
        case 1: return g;
        case 2: return b;
        default: abort();
    };
}

//! Print this colour to a string
char* RayColour::snprint(char *buf, int maxLen) const
{
    snprintf(buf,maxLen,"R:%.03f G:%.03f B:%.03f",r,g,b);
    buf[maxLen-1] = '\0';
    return buf;
}

//! Set all components of the colour
void DisplayColour::set(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

//! Find max and min in image, for conversion range
LinearColourAdapter::LinearColourAdapter(RayImage *image)
{
    if( (image->width()==0) || (image->height() == 0) ) {
        m_min = 0.0;
        m_max = 1.0;
        return;
    }

    /* Find the image max and min */
    m_min = image->at(0,0).m_colour[0];
    m_max = image->at(0,0).m_colour[0];
    for(int i=0; i<image->width(); ++i) {
        for(int j=0; j<image->height(); ++j) {
            for(int k=0; k<3; ++k) {
                if( image->at(i,j).m_colour[k] < m_min ) 
                    m_min = image->at(i,j).m_colour[k];
                if( image->at(i,j).m_colour[k] > m_max )
                    m_max = image->at(i,j).m_colour[k];
            }
        }
    }
}

//! Straightforward linear colour conversion
void LinearColourAdapter::convert(Ray* source, DisplayColour* dest)
{
    dest->r = (source->m_colour.r-m_min) / (m_max-m_min);
    if( dest->r > 1.0 ) dest->r = 1.0;
    dest->g = (source->m_colour.g-m_min) / (m_max-m_min);
    if( dest->g > 1.0 ) dest->g = 1.0;
    dest->b = (source->m_colour.b-m_min) / (m_max-m_min);
    if( dest->b > 1.0 ) dest->b = 1.0;
}

//! Depth mapping
void DepthAdapter::convert(Ray *source, DisplayColour *dest)
{
    // Rays which intersect nothing are treated as maximally distant
    if( source->m_intersectDist < 0 ) {
        dest->set(0, 0, 0);
        return;
    }

    double distScale = source->m_intersectDist / m_maxDepth;
    if(distScale>1.0) distScale = 1.0;
    // Reverse the scale, so near objects are bright and distant dark
    dest->set(1.0-distScale, 1.0-distScale, 1.0-distScale);
}

