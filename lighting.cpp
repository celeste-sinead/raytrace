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
    if( obj && (lightRay.m_intersectDist < toHere.length() ) ) {
        // If an intersection was found and is closer than this light...
        result.m_dir.set(1,0,0);
        result.m_intensity.set(0,0,0);
    } else {
        result.m_dir = -lightRay.m_dir;
        
        /* Now, calculate the decrease in intensity due to distance
         * (Calculation comes from surface area of a sphere) */
        double scale = 1.0 / (4.0*M_PI*toHere.length()*toHere.length()); 

        result.m_intensity = m_intensity*scale;
    }
    return result;
}

