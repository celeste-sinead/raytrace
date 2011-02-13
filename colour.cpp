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

#include "colour.h"
#include "ray.h"

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

//! Straightforward linear colour conversion
void LinearColourAdapter::convert(Ray* source, DisplayColour* dest)
{
    dest->r = source->m_colour.r / m_max;
    if( dest->r > 1.0 ) dest->r = 1.0;
    dest->g = source->m_colour.g / m_max;
    if( dest->g > 1.0 ) dest->g = 1.0;
    dest->b = source->m_colour.b / m_max;
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

