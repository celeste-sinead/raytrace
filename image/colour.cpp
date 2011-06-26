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
#include <cmath>

#include "colour.h"

#include "trace/ray.h"
#include "image.h"
#include "rayImage.h"

//! Set all components of the colour
void RayColour::set(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

//! Magnitude of this colour
double RayColour::magnitude()
{
    return sqrt(r*r + g*g + b*b);
}

RayColour& RayColour::operator=(const RayColour& other)
{
    set(other.r, other.g, other.b);
    return *this;
}
RayColour& RayColour::operator=(double other)
{
    set(other, other, other);
    return *this;
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


//! Straightforward linear colour conversion
Image& LinearHDRToDisplay::apply(Image &img)
{
    for (unsigned i=0; i < img.height(); ++i) {
        for (unsigned j=0; j < img.width(); ++j) {
            for (unsigned k=0; k < img.colours(); ++k) {
                img.at(i,j,k) = (img.at(i,j,k)-m_min) / (m_max - m_min);
                if (img.at(i,j,k) > 1.0) img.at(i,j,k) = 1.0;
                if (img.at(i,j,k) < 0.0) img.at(i,j,k) = 0;
            }
        }
    }

    return img;
}

// Converts double colour to int colour
unsigned long intColour(double value, unsigned bits) {
    unsigned long ret = value * (double)((1<<bits) - 1);
    return ret % (1<<bits);
}

