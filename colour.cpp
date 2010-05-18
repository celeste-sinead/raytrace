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

//! Set all components of the colour
void RayColour::set(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

//! Print this colour to a string
char* RayColour::snprint(char *buf, int maxLen) const
{
    snprintf(buf,maxLen,"R:%.03f G:%.03f B:%.03f",r,g,b);
    buf[maxLen-1] = '\0';
    return buf;
}

//! Straightforward linear colour conversion
void LinearColourAdapter::convert(RayColour* source, DisplayColour* dest)
{
    dest->r = source->r / m_max;
    if( dest->r > 1.0 ) dest->r = 1.0;
    dest->g = source->g / m_max;
    if( dest->g > 1.0 ) dest->g = 1.0;
    dest->b = source->b / m_max;
    if( dest->b > 1.0 ) dest->b = 1.0;
}

