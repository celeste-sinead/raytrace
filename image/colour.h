/******************************************************************************
 * colour.h
 * Copyright 2010 Iain Peet
 *
 * Defines colour objects used in raytracing.
 *
 * The RayColour class is intended for ray trace calculations.  It uses double
 * precision math to track colours within graphics space.  These are unbounded
 * intensity values, which may be translated to a more subjective colour space
 * just in time for display.  Within tracing calculations, arithmetic and
 * assignment of a colour set is common, so it is worthwhile to have a class
 * with overloaded operators.
 *
 * Once tracing is completed and we move into the realm of image processing,
 * it is more useful to view the image as a set of monochrome matrices;
 * one for each colour.  So the colour objects from the tracing domain
 * give way to multiple arrays, each containing one colour component.
 *
 * Within the realm of tracing, intensities are permitted to be unbounded
 * positive, i.e. high dynamic range.  Before the image can be displayed,
 * colours must be mapped into the [0,1.0] display range.
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

#ifndef colour_h_
#define colour_h_

#include "image/transform.h"

class Ray;
class RayImage;

enum ColourIndices {
    RED, GREEN, BLUE
};

/* Converts the unbounded positive HDR colours used in tracing
 * into the [0,1] range used for RGB display, with a simple
 * linear scale */
class LinearHDRToDisplay : public ImageTransform {
private:
    /* Range of intensities for linear range: */
    double m_min;
    double m_max;  

public:
    LinearHDRToDisplay(double min, double max) :
        m_min(min), m_max(max)
        { }

    virtual Image& apply(Image &img);
};

/* Converts a colour represented by a double in the range [0,1]
 * into an int of the specified number of bits */
unsigned long intColour(double value, unsigned bits);

/** A colour, for use within graphics calculations.  Intensity is positive,
 *  without bound.  */
class RayColour {
public:
    /** RGB intensity.  These are in range [0.0,infinity] */
    double r;
    double g;
    double b;

    RayColour() : r(0.0), g(0.0), b(0.0)                                   { /* n/a */ }
    RayColour(double cr, double cg, double cb) : r(cr), g(cg), b(cb)       { /* n/a */ }
    RayColour(const RayColour &other) : r(other.r), g(other.g), b(other.b) { /* n/a */ }
    
    void set(double r, double g, double b);

	//! Length of this colour (intepreted as a 3-vector)
	double magnitude();

    //! Assignment
    RayColour& operator=(const RayColour& other);
    RayColour& operator=(double other);
    //! Elementwise multiplication:
    RayColour operator*(const RayColour& other);
    //! Scaling:
    RayColour operator*(double other);
    friend RayColour operator*(double left, const RayColour& right);
    //! Elementwise addition/subtraction:
    RayColour operator+(const RayColour& other);
    RayColour operator-(const RayColour& other);
    //! Access colours r, g, b (convenient for iteration)
    double& operator[](int inx);
    
    //! Print this colour to a string, with maximum length.  Return the string.
    char* snprint(char* buf, int maxLen) const;
};

#endif

