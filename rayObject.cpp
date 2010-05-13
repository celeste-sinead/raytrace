/******************************************************************************
 * rayObject.cpp
 * Copyright 2010 Iain Peet
 *
 * Implements the base of some object in the ray graphics universe which
 * affects rays in some way.
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

#include <math.h>

#include "rayObject.h"

//! Checks if a ray intersects this object.  
bool RayObject::intersects(Ray& inbound)
{
    /* First, the coarse intersection check.  
     * Idea is simple - we see if the ray passes within a the circular 
     * intersection of the sphere and a plane normal to the vector from
     * the endpoint of the ray and the center of the sphere.  ( also,
     * the length of opposite in a triangle formed by the vector from the
     * endpoint to the centroid, and the direction of the ray, is less than
     * radius of the sphere ) 
     * Hey, it's simple if you draw a diagram, anyway. */
  
    // Vector from ray endpoint to centre of sphere
    RayVector toCent = m_origin - inbound.m_endpoint;
    // Unit vector of toCent 
    RayVector uToCent (toCent);
    uToCent.unitify();
    /* The dot product gives us the length of the adjacent side of a triangle
     * similar to the triangle between the endpoint, sphere origin, and 
     * the intersection, with the hypotenuse scaled to unit length */
    double adjacent = inbound.m_dir.dot(uToCent);
    /* Negative result means the vector is pointing *away* from the center
     * of the sphere */
    if(adjacent <= 0.0) return false;
    // Find the length of the opposite side of the triangle
    double opposite = sqrt( 1 /* hyp is a unit vec */ - (adjacent*adjacent) );
    // Find the intersect radius of the ray (law of similar triangles)
    double intersectRad = toCent.length() * (opposite / adjacent); 
    if( intersectRad > (m_radius + m_radius*0.0001) /* (tolerance) */ ) {
	return false;
    }
    
    /* Note that coarse intersect checking is tested in sphere.cpp, 
     * since a RayObject is pure virtual, and a sphere only uses coarse
     * intersect check */
   
    /* The ray enters the object's containing sphere.  Need to do a finer, 
     * geometry-dependent intersect check to determine if there is an actual
     * intersection */
    return intersectsFine(inbound);
}

