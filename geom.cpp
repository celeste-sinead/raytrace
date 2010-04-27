/******************************************************************************
 * geom.cpp 
 * Copyright 2010 Iain Peet
 *
 * Implements basic geometric primitives.
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

#include <cmath>

#include "geom.h"


void RayVector::setX(double x)
{
    m_x = x;
    calcLength();
}
void RayVector::setY(double y)
{
    m_y = y;
    calcLength();
}

void RayVector::setZ(double z)
{
    m_z = z;
    calcLength();
}

//! Make this a unit vector.
void RayVector::unitify()
{
    // Cneck if already at unit length
    if( fabs(m_length-1) < 1E-5 ) return;
    
    // Scale to unit length
    m_x /= m_length;
    m_y /= m_length;
    m_z /= m_length;
    
    calcLength();
}

//! Compute the dot product of this and another vector
double RayVector::dot(const RayVector& other) const
{
    return (m_x*other.x()) + (m_y*other.y()) + (m_z*other.z());
}

//! Compute distance between this vector and another
double RayVector::dist(const RayVector& other) const
{
    return ( (*this) - other ).length();
}

/** Vector addition and subtraction */
RayVector RayVector::operator+(const RayVector& other) const
{
    return RayVector( m_x+other.x(), m_y+other.y(), m_z+other.z() );
}
RayVector RayVector::operator-(const RayVector& other) const 
{
    return RayVector( m_x-other.x(), m_y-other.y(), m_z-other.z() );
}

//! Vector negation - reverse direction
RayVector RayVector::operator-() const
{
    return RayVector( -m_x, -m_y, -m_z );
}

//! Calculates the length of this vector
void RayVector::calcLength()
{
    m_length = sqrt( (m_x*m_x) + (m_y*m_y) + (m_z*m_z) );
}
