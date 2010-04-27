/******************************************************************************
 * sphere.cpp
 * Copyright 2010 Iain Peet
 *
 * Implements a simple spherical solid.
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

#include "sphere.h"
#include "ray.h"
#include "colour.h"
#include "geom.h"

//! Colours an intersecting ray
void Sphere::colour(Ray& inbound)
{
    inbound.m_colour.r = 1.0;
    inbound.m_colour.g = 1.0;
    inbound.m_colour.b = 1.0;
}

//! Determines if a ray intersects this sphere
bool Sphere::intersectsFine(Ray& inbound)
{
    /* Idea is simple - we see if the ray passes within a the circular 
     * intersection of the sphere and a plane normal to the vector from
     * the endpoint of the ray and the center of the sphere.  ( also,
     * the length of third line in a triangle formed by the vector from the
     * endpoint to the centroid, and the direction of the ray, is less than
     * radius of the sphere ) */
  
    // Vector from centre of sphere to endpoint of ray
    RayVector fromCent = inbound.m_endpoint - m_origin;
    // Unit vector of fromCent
    RayVector uFromCent (fromCent);
    uFromCent.unitify();
    // The magic of dot products:
    double cosOmega = inbound.m_dir.dot(uFromCent);
    /* Negative result means the vector is pointing *away* from the center
     * of the sphere */
    if(cosOmega <= 0.0) return false;
    // cosOmega is also the adjacent of a triangle, we want the opposite -
    double opposite = sqrt( 1 - (cosOmega*cosOmega) );
    // Find the intersect radius of the ray
    double intersectRad = opposite * (fromCent.length()/cosOmega);
    return intersectRad <= m_radius;
}
