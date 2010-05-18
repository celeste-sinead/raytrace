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

#include <cstdio>
#include <cmath>
#include <iputil/unit.h>
#include <iputil/trace.h>

#include "geom.h"

static trc_ctl_t geomTrace = {
    TRC_DFL_LVL,
    "GEOM",
    TRC_STDOUT
};
#define TRACE(level, args...) \
    trc_printf(&geomTrace,level,1,args)

//! Assignment
RayVector& RayVector::operator=(const RayVector& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    calcLength();
    return *this;
}

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

void RayVector::set(double x, double y, double z)
{
    m_x = x;
    m_y = y;
    m_z = z;
    calcLength();
}

//! Make this a unit vector.
RayVector & RayVector::unitify()
{
    // Cneck if already at unit length
    if( fabs(m_length-1) < 1E-5 ) return *this;
    
    // Scale to unit length/
    m_x /= m_length;
    m_y /= m_length;
    m_z /= m_length;
    
    calcLength();
    
    return *this;
}

//! Compute the dot product of this and another vector
double RayVector::dot(const RayVector& other) const
{
    double theDot = (m_x*other.x()) + (m_y*other.y()) + (m_z*other.z());
    TRACE(TRC_DTL,"(%.03f, %.03f, %.03f) . (%.03f, %.03f, %.03f) "
        " = %.03f\n", m_x, m_y, m_z,
	other.m_x, other.m_y, other.m_z, theDot);
    return theDot;
}

//! Compute the cross product of this and another vecgtor
RayVector RayVector::cross(const RayVector& other) const
{
    double crossX = (m_y*other.m_z) - (m_z*other.m_y);
    double crossY = -( (m_x*other.m_z) - (m_z*other.m_x) );
    double crossZ = (m_x*other.m_y) - (m_y*other.m_x);
    RayVector ret (crossX, crossY, crossZ);
    TRACE(TRC_DTL,"(%.03f, %.03f, %.03f) x (%.03f, %.03f, %.03f) "
        " = (%.03f, %.03f, %.03f)\n",
	m_x,m_y,m_z,
	other.m_x, other.m_y, other.m_z,
        ret.m_x, ret.m_y, ret.m_z );
    return ret;
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

//! Scalar multiply
RayVector RayVector::operator*(const double scalar) const
{
    return RayVector( m_x*scalar, m_y*scalar, m_z*scalar );
}
RayVector operator*(const double scalar, const RayVector &vec) 
{
    return RayVector( vec.m_x*scalar, vec.m_y*scalar, vec.m_z*scalar );
}

//! Scalar divice
RayVector RayVector::operator/(const double scalar) const
{
    return RayVector( m_x/scalar, m_y/scalar, m_z/scalar );
}

//! Comparison
bool RayVector::operator==(const RayVector& other) const
{
    if( fabs( m_x - other.m_x ) > fabs(m_x*1E-10) ) return false;
    if( fabs( m_y - other.m_y ) > fabs(m_y*1E-10) ) return false;
    if( fabs( m_z - other.m_z ) > fabs(m_z*1E-10) ) return false;
    return true;
}

//! Calculates the length of this vector
void RayVector::calcLength()
{
    m_length = sqrt( (m_x*m_x) + (m_y*m_y) + (m_z*m_z) );
}

//! Print to string and return it
char* RayVector::snprint(char* buf, int maxLen) const
{
    snprintf(buf,maxLen,"(%.03f, %.03f, %.03f)",m_x,m_y,m_z);
    buf[maxLen-1] = '\0';
    return buf;
}


START_TEST_FN(vector_geom,"Vector Algebra")
    RayVector vec1 (1.0,0.0,0.0);
    RayVector vec2 (0.0,1.0,0.0);
    RayVector cross = vec1.cross(vec2);
    TEST_CONDITION( cross == RayVector(0.0,0.0,1.0), "i x j = k\n" );
    
    cross = vec2.cross(vec1);
    TEST_CONDITION( cross == RayVector(0.0,0.0,-1.0), "j x i = -k\n" );
    
    vec1.set(1,1,1);
    vec2.set(-1,1,1);
    cross = vec1.cross(vec2);
    TEST_CONDITION( (fabs(vec1.dot(cross)) < 1E-3)
        && ( fabs(vec2.dot(cross)) < 1E-3 ),
	"check s x p\n\n");
    
END_TEST_FN
