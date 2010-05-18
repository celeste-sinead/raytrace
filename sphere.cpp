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
#include <iputil/unit.h>

#include "sphere.h"
#include "ray.h"
#include "colour.h"
#include "geom.h"
#include "world.h"

//! Colours an intersecting ray
bool Sphere::colour(Ray *inbound, World *world)
{
    // Hey, it's all stubby!
    inbound->m_colour.r = 1.0;
    inbound->m_colour.g = 1.0;
    inbound->m_colour.b = 1.0;
    return true;
}

//! Determines if a ray intersects this sphere
bool Sphere::intersectsFine(Ray* inbound)
{
    /* The coarse intersect check performed in RayObject::intersects()
     * determins if the ray intersects a containing a sphere.  This IS
     * a sphere, so if the coarse check succeeded, there is an intersect. */
    return true;
}

//! Check intersect detection for sphere.
START_TEST_FN(sphere_intersect,"Sphere Intersect Detection")
    Sphere s ( Coord(0.0,0.0,0.0), 1.0);
    Ray r (1 /* no reflection */);
   
    RayVector endpt (2.0, 0.0, 0.0);
    
    /* Test a ray directed at the centre of the sphere */
    RayVector direct_dir (-1.0, 0.0, 0.0);
    r.m_endpoint = endpt;
    r.m_dir = direct_dir;
    TEST_CONDITION( s.intersects(&r), "Direct intersection check\n");
    
    /* Test a non-centred intersection */
    RayVector indirect_dir (-2.0, 0.5, 0.0);
    indirect_dir.unitify();
    r.m_dir = indirect_dir;
    TEST_CONDITION( s.intersects(&r), "Indirect intersection check\n");
    
    /* Test an edge intersection */
    // Some geometry gives us this vector, which just touches the edge.
    RayVector edge_dir (-1.5, sqrt(3)/2.0, 0.0);
    edge_dir.unitify();
    r.m_dir = edge_dir;
    TEST_CONDITION( s.intersects(&r), "Edge intersection check\n");
    
    /* Test the complete wrong direction */
    RayVector opposite_dir (1.0, 0.0, 0.0);
    r.m_dir = opposite_dir;
    TEST_CONDITION( ! s.intersects(&r), "Opposite direction miss check\n");
    
    /* Normal to direction of sphere */
    RayVector normal_dir (0.0, 1.0, 0.0);
    r.m_dir = normal_dir;
    TEST_CONDITION( ! s.intersects(&r), "Normal miss check\n");
    
    /* Near miss */
    RayVector near_dir (-1.5, sqrt(3)/2.0+0.01, 0.0);
    near_dir.unitify();
    r.m_dir = near_dir;
    TEST_CONDITION( ! s.intersects(&r), "Near miss check\n");
    
END_TEST_FN
