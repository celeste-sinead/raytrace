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
#include <iputil/unit.h>

#include "ray.h"
#include "rayObject.h"
#include "world.h"

static trc_ctl_t rayObjectTrc = {
    TRC_DFL_LVL,
    "RAY-OBJ",
    TRC_DFL_PRINT
};
#define TRACE(level, args...) \
    trc_printf(&rayObjectTrc,(level),1,args)

//! Checks if a ray intersects this object.  
double BaseSphere::sphereIntersectDist(Ray *inbound)
{
    /* Idea is simple - we find the minimum distance from the ray
     * to the centre of a sphere containing the object.  If this
     * distance is greater than the sphere's radius, we know the
     * ray does not intersect.  Otherwise, we need to make a 
     * more exact check. */
  
    // Vector from ray endpoint to centre of sphere
    RayVector toCent = m_origin - inbound->m_endpoint;
    // toCent is the hypotenuse of the right triangle
    double hypotenuse = toCent.length();
    /* Dot product projects toCent onto the unit vector of the
     * adjacent edge, giving us the adjacent length */
    double adjacent = inbound->m_dir.dot(toCent);
    /* Negative result means the vector is pointing *away* from the center
     * of the sphere */
    if(adjacent <= 0.0) {
        TRACE(TRC_DTL,"Coarse intersect adjacent: %f\n",adjacent);
        return -1.0;
    }
    /* Find the length of the opposite edge, which is also the minimum
     * distance between the ray and the centre of the sphere */
    double minDist = sqrt( (hypotenuse*hypotenuse) - (adjacent*adjacent) );
   
    TRACE(TRC_DTL,"Coarse intersect min distance: %f\n",minDist);
    if( minDist > (m_radius + m_radius*0.0001) /* (tolerance) */ ) {
        return -1.0;
    }

#warning Stub!
    return 1.0;
}    

//! Find the point where the ray intersects the sphere
Coord BaseSphere::intersectPoint(Ray *inbound) {
#warning Stub!
    return Coord();
}

//! Find the normal vector at the intersection point
RayVector BaseSphere::normal(const Coord &point) {
#warning Stub!
    return RayVector();
}

//! Colour a ray
bool Sphere::colour(Ray* inbound, World* world) {
#warning Stub!
    inbound->m_colour = m_reflectivity;
    return true;
}

//! Check intersect detection for sphere.
START_TEST_FN(sphere_intersect,"Sphere Intersect Detection")
    Sphere s ( Coord(0.0,0.0,0.0), 1.0, RayColour(1.0,1.0,1.0));
    Ray r (1 /* no reflection */);
   
    RayVector endpt (2.0, 0.0, 0.0);
    
    /* Test a ray directed at the centre of the sphere */
    RayVector direct_dir (-1.0, 0.0, 0.0);
    r.m_endpoint = endpt;
    r.m_dir = direct_dir;
    TEST_CONDITION( s.intersectDist(&r) >= 0, "Direct intersection check\n");
    
    /* Test a non-centred intersection */
    RayVector indirect_dir (-2.0, 0.5, 0.0);
    indirect_dir.unitify();
    r.m_dir = indirect_dir;
    TEST_CONDITION( s.intersectDist(&r) >= 0, "Indirect intersection check\n");
    
    /* Test an edge intersection */
    // Some geometry gives us this vector, which just touches the edge.
    RayVector edge_dir (-1.5, sqrt(3)/2.0, 0.0);
    edge_dir.unitify();
    r.m_dir = edge_dir;
    TEST_CONDITION( s.intersectDist(&r) >= 0, "Edge intersection check\n");
    
    /* Test the complete wrong direction */
    RayVector opposite_dir (1.0, 0.0, 0.0);
    r.m_dir = opposite_dir;
    TEST_CONDITION( s.intersectDist(&r) < 0, "Opposite direction miss check\n");
    
    /* Normal to direction of sphere */
    RayVector normal_dir (0.0, 1.0, 0.0);
    r.m_dir = normal_dir;
    TEST_CONDITION( s.intersectDist(&r) < 0, "Normal miss check\n");
    
    /* Near miss */
    RayVector near_dir (-1.5, sqrt(3)/2.0+0.01, 0.0);
    near_dir.unitify();
    r.m_dir = near_dir;
    TEST_CONDITION( s.intersectDist(&r) < 0, "Near miss check\n");
    
END_TEST_FN

