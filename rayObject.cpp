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
#include <iputil/trace.h>

#include "rayObject.h"

static trc_ctl_t rayObjectTrc = {
    TRC_WARN,
    "RAY-OBJ",
    TRC_DFL_PRINT
};
#define TRACE(level, args...) \
    trc_printf(&rayObjectTrc,(level),1,args)


//! Checks if a ray intersects this object.  
bool RayObject::intersects(Ray& inbound)
{
    /* First, the coarse intersection check.  
     * Idea is simple - we find the minimum distance from the ray
     * to the centre of a sphere containing the object.  If this
     * distance is greater than the sphere's radius, we know the
     * ray does not intersect.  Otherwise, we need to make a 
     * more exact check. */
  
    // Vector from ray endpoint to centre of sphere
    RayVector toCent = m_origin - inbound.m_endpoint;
    // toCent is the hypotenuse of the right triangle
    double hypotenuse = toCent.length();
    /* Dot product projects toCent onto the unit vector of the
     * adjacent edge, giving us the adjacent length */
    double adjacent = inbound.m_dir.dot(toCent);
    /* Negative result means the vector is pointing *away* from the center
     * of the sphere */
    if(adjacent <= 0.0) {
        TRACE(TRC_DTL,"Coarse intersect adjacent: %f\n",adjacent);
        return false;
    }
    /* Find the length of the opposite edge, which is also the minimum
     * distance between the ray and the centre of the sphere */
    double minDist = sqrt( (hypotenuse*hypotenuse) - (adjacent*adjacent) );
   
    TRACE(TRC_DTL,"Coarse intersect min distance: %f\n",minDist);
    if( minDist > (m_radius + m_radius*0.0001) /* (tolerance) */ ) {
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

