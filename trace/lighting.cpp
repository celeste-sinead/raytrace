/******************************************************************************
 * lighting.cpp
 * Copyright 2011 Iain Peet
 *
 * Defines entities in the world which cast light on their surroundings
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

#include "lighting.h"
#include "ray.h"
#include "world.h"
#include "rayObject.h"

Lighting PointSource::lightingAt(Coord * point, World *world )
{
    Ray lightRay;
    RayVector toHere = m_origin - *point;
    lightRay.m_endpoint = *point;
    lightRay.m_dir = toHere;
    lightRay.m_dir.unitify();
    lightRay.nudge();

    RayObject * obj = world->intersect(&lightRay);

    Lighting result;
    result.m_dir.set(1,0,0); // want nonzero vector incase somebody tries to math it
    result.m_intensity.set(0,0,0);

    // If an intersection was found and is closer than this light...
    if( obj && (lightRay.m_intersectDist < toHere.length() ) ) {
        if( dynamic_cast<RayObject*>(this) != obj ) {
            /* Some entities will be both lights and objects, and will want to 
             * inherit this functionality.  This check is in place to make sure
             * that a point/light object does not obscure itself.  dynamic_cast
             * retrieves the correct pointer for comparison for multiply
             * inherited class, and zero if this is not an object.  */
            return result;
        }
    } 

    /* Now, calculate the decrease in intensity due to distance
     * (Calculation comes from surface area of a sphere) */
    double scale = 1.0 / (4.0*M_PI*toHere.length()*toHere.length()); 
    result.m_intensity = m_intensity*scale;
    result.m_dir = -lightRay.m_dir;

    return result;
}

bool SphereSource::colour(Ray* inbound, World* world)
{
    /* Calculate decrease in intensity due to distance, as above */
    double dist = inbound->m_intersectDist;
    inbound->m_colour = m_intensity;
    return true;
}

