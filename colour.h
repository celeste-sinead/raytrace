/******************************************************************************
 * colour.h
 * Copyright 2010 Iain Peet
 *
 * Defines a colour, for the purposes of raytracing calculations.  Use double
 * precision math to track colours within graphics space.  These are unbounded
 * intensity values, which may be translated to a more subjective colour space
 * just in time for display.
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

/** A colour, for use within graphics calculations.  Intensity is positive,
 *  without bound.  */
struct RayColour {
    /** RGB intensity.  These are in range [0.0,infinity] */
    double r;
    double g;
    double b;

    RayColour() : r(0.0), g(0.0), b(0.0)                                  { /* n/a */ }
    RayColour(double cr, double cg, double cb) : r(cr), g(cg), b(cb)      { /* n/a */ }
    RayColour(const RayColour &other) : r(other.r), g(other.g), b(other.b) { /* n/a */ }
};

/** A color, for displaying.  Functions for transforming from internal ray colors
 *  to display colors are included.  (They're rather arbitrary!) */
struct DisplayColour {
    /** RGB intensity.  Kept in double precision, in the range [0,1.0], so we can
     *  easily convert to arbitrary integer color depth */
    double r;
    double g;
    double b;

    /** Convert to arbitrary integer color depth.  Depth is in bits */
    unsigned long red(unsigned int depth)
        { return r*(1<<depth); }
    unsigned long green(unsigned int depth)
        { return g*(1<<depth); }
    unsigned long blue(unsigned int depth)
        { return b*(1<<depth); }

    /********* Various conversion functions **********/

    /** Convert using a linear scale.  Simple, easy, and not very pretty */
    void fromRayLinear(const RayColour & colour, double maximum);
};

#endif

