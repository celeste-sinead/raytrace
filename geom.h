/******************************************************************************
 * coord.h
 * Copyright 2010 Iain Peet
 *
 * Defines basic geometric primitives, e.g co-ordinates and vectors.
 * We're going to be using both geometric vectors and STL vectors in this
 * project, for extra fun.
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

#ifndef coord_h_
#define coord_h_

/** This is a vector of the linear algebra variety, not the data structure */
class RayVector {
private:
    double m_x;
    double m_y;
    double m_z;

    //! Redundant, but pre-calculated.
    double m_length;

public:
    RayVector() : m_x(0.0), m_y(0.0), m_z(0.0) 
        {}
    RayVector(double cx, double cy, double cz) : m_x(cx), m_y(cy), m_z(cz) 
        {}
    RayVector(const RayVector &other) :
        m_x(other.m_x), m_y(other.m_y), m_z(other.m_z) 
        {}

    double x() const { return m_x; }
    void setX(double x);
    double y() const { return m_y; }
    void setY(double y);
    double z() const { return m_z; }
    void setZ(double z);

    //! Make this vector a unit vector
    void unitify();

    //! Compute the dot product of this vector with another
    double dot(const RayVector & other) const;

    //! Compute the length of this vector
    double length() const { return m_length; }

    /** Compute the magnitude of (this-other) (if this and other are really
     *  co-ordinates, this is the distance between the two */
    double dist(const RayVector & other) const;
    
    /** Vector addition / subtraction */
    RayVector operator+(const RayVector & other) const;
    RayVector operator-(const RayVector & other) const;
    
    /** Unary negation - reverse direction of this vector */
    RayVector operator-() const;
    
protected:
    //! Calculates current length of this vector
    void calcLength();
};

/** Yeah, yeah, yeah, co-ordinates are vectors, really.  But it's nice to
 *  make a nod to the sligh abstract difference */
typedef RayVector Coord;

#endif //coord_h_
