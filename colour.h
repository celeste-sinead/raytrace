/******************************************************************************
 * colour.h
 * Copyright 2010 Iain Peet
 *
 * Defines colour objects used in raytracing.
 *
 * The RayColour class is intended for ray trace calculations.  It uses double
 * precision math to track colours within graphics space.  These are unbounded
 * intensity values, which may be translated to a more subjective colour space
 * just in time for display.
 *
 * The DisplayColour class is a more typical RGB colour class.  It uses 
 * double values in the range [0.0,1.0] to represent RGB colour components.
 * 
 * Also defined are the ColourAdapter classes, which implement various
 * schemes for translating between the high dynamic range RayColour and the
 * display-friendly DisplayColour.
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

class Ray;
class RayImage;

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

/** A displayable colour.  That is, a colour whose values are all constrained
 *  to lie in the range [0,1].  The main difference between a RayColour and a
 *  DisplayColour is logical (different allowable ranges) */
class DisplayColour: public RayColour {
public:
    DisplayColour() : RayColour() {}
    DisplayColour(double cr, double cg, double cb) : RayColour(cr, cg, cb) {}
    DisplayColour(const DisplayColour &other) : RayColour(other) {}

    /** Convert to arbitrary integer color depth.  Depth is in bits */
    unsigned long red(unsigned int depth)
        { return r*((1<<depth) - 1); }
    unsigned long green(unsigned int depth)
        { return g*((1<<depth) - 1); }
    unsigned long blue(unsigned int depth)
        { return b*((1<<depth) - 1); }

    //! Assignment
    DisplayColour& operator=(const DisplayColour& other);
    DisplayColour& operator=(double other);
    //! Elementwise multiplication:
    DisplayColour operator*(const DisplayColour& other);
    //! Scaling:
    DisplayColour operator*(double other);
    friend DisplayColour operator*(double left, const DisplayColour& right);
    //! Elementwise addition/subtraction:
    DisplayColour operator+(const DisplayColour& other);
    DisplayColour operator-(const DisplayColour& other);
    //! Access colours r, g, b (convenient for iteration)
    double& operator[](int inx);
};

/** Provides a strategy for converting between a high dynamic range RayColour
 *  and a displayable DisplayColour */
class ColourAdapter {
public:
    /** Converts a traced ray (which should have colour, depth, child, etc.
     *  information) into a displayable colour 
     *  @param source The ray to colour
     *  @param dest   The DisplayColour instance to fill */
    virtual void convert(RayColour * source, DisplayColour * dest) = 0;  
};

/** Implements a simple linear scaling */
class LinearColourAdapter: public ColourAdapter {
private:
    /** Range of intensities for linear range: */
    double m_min;
    double m_max;  
public:
	LinearColourAdapter(double min, double max) : 
        m_min(min), m_max(max) 
        {}  
    LinearColourAdapter(RayImage *image);

    virtual void convert(RayColour * source, DisplayColour * dest);
};

#endif

