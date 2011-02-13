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

#include "lighting.h"
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
    /* Find the intersections between the inbound unit vector and
     * this sphere. You will need a whiteboard to verify.*/

    // Vector from ray endpoint to centre of sphere
    RayVector toCent = m_origin - inbound->m_endpoint;

    // Square of the distance from ray encpoint to centre of sphere
    double cSq = toCent.length();
    cSq = cSq * cSq;

    // Distance from ray endpoint to point nearest sphere centre
    double D = inbound->m_dir.dot(toCent);

    // Discriminant of the intersection distance quadratic:
    double discr = (m_radius*m_radius) + (D*D) - cSq;

    // Discriminant < 0 indicates no intersection
    if(discr < 0) {
        TRACE(TRC_DTL,"Ray misses sphere.");
        return -1.0;
    }

    // Calculate the two intersect distances
    double sqrtDiscr = sqrt(discr);
    double d1 = D + sqrtDiscr;
    double d2 = D - sqrtDiscr;
    // Note that d2 < d1 always

    if( (d1<0.0) && (d2<0.0) ) { 
        // Both intersections are 'behind' the endpoint
        TRACE(TRC_DTL,"Sphere is beyond ray endpoint.");
        return -1.0;
    }
    // d2 is still behind enpoint, d1 is result
    if( d2 < 0.0 ) {
        TRACE(TRC_DTL,"Ray intersects sphere form inside, dist %f\n",d1);
        return d1;
    }
    // both are ahead, d2 is smaller
    TRACE(TRC_DTL,"Ray hits sphere, dist %f\n",d2);
    return d2;
}    

//! Find the normal vector at the intersection point
RayVector BaseSphere::normal(const Coord &point) {
    return (point - m_origin).unitify();
}

//! Colour a ray
bool Sphere::colour(Ray* inbound, World* world) {
    // Diffuse light:
    RayColour colour = m_diffusivity * world->m_globalDiffuse;

    /* Add contributions of all light sources */
    RayVector intersect = inbound->m_endpoint + 
        inbound->m_dir * inbound->m_intersectDist;;
    RayVector interNorm = -normal(intersect);
    for(unsigned i=0; i<world->lights().size(); ++i) {
        Lighting cur = world->lights().at(i)->lightingAt(&intersect, world);

        double scale = cur.m_dir.dot(interNorm);
        if(scale<0.0) scale = 0.0;
        
        colour = colour + (m_diffusivity * cur.m_intensity * scale);
    }

    /* Attempt to trace a reflection */
    Ray * reflect = inbound->createParent();
    if(reflect && (m_reflectivity.magnitude() != 0) ) {
        reflect->m_endpoint = intersect;
        RayVector incNormal (interNorm.dot(inbound->m_dir) * interNorm);
        RayVector incTangent ( (inbound->m_dir) - incNormal );
        reflect->m_dir = incTangent - incNormal;
        reflect->nudge();
        
        if(world->trace(reflect)) {
            colour = colour + (m_reflectivity * reflect->m_colour);
        }
    }

    inbound->m_colour = colour;
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

