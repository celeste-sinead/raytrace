/******************************************************************************
 * world.h
 * Copyright 2010 Iain Peet
 *
 * Provides the World class, which contains all visible objects, and is
 * responsible for actually tracing rays.
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

#include <vector>
#include <cmath>

#include "world.h"

#include "image/colour.h"
#include "util/trace.h"
#include "ray.h"
#include "rayObject.h"

using std::vector;

static trc_ctl_t worldTrace = {
    TRC_DFL_LVL,
    "WORLD",
    TRC_STDOUT
};
#define TRACE(level, args...) \
   trc_printf(&worldTrace,level,1,args)

//! Removes an object from the object list
RayObject* World::remove(int index)
{
    vector<RayObject*>::iterator elem = m_objects.begin();
    elem += index;
    RayObject * removed = 0;
    if( elem != m_objects.end() ) {
         removed = *elem;
         m_objects.erase(elem);
    }
    return removed;
}

//! Trace a ray
bool World::trace(Ray* ray)
{
    ray->m_colour = m_defaultColour;
    RayObject * closest = 0;
    double closestDist = 0.0;
   
    /* See if the ray hits any objects */
    for(int i=0; i<size(); ++i) {
        double curDist = at(i)->intersectDist(ray);
        TRACE(TRC_DTL, "Object %d distance: %f\n", i, curDist);

        if(curDist >= 0.0) { // Actually intersects
            if( (!closest) || (curDist < closestDist) ) {
                // First intersection, or smallest intersection yet
                closest = at(i);
                closestDist = curDist;
            }
        }
    }
    
    if( !closest ) {
        // Ray hits no objects, use background colour
        TRACE(TRC_INFO,"Ray hit no objects, given background colour.\n");
        ray->m_colour = m_globalDiffuse;
        ray->m_intersectDist = -1.0;
        return true;
    }

    ray->m_intersectDist = closestDist;
    if( closest->colour(ray, this) ) {
        // Found colour successfully
        TRACE(TRC_INFO,"Got ray colour from intersect object.\n");
        return true;
    }
   
    TRACE(TRC_WARN,"Failed to trace ray.\n");
    return false;   
}

//! Find the first object intersecting a ray
RayObject * World::intersect(Ray * ray)
{
    RayObject * closest = 0;
    double closestDist = -1.0;

    /* Look for objects for intersections */
    for(int i=0; i<size(); ++i) {
        double curDist = at(i)->intersectDist(ray);
        if(curDist >= 0.0) {
            if( (!closest) || (curDist < closestDist) ) {
                closest = at(i);
                closestDist = curDist;
            }
        }
    }

    ray->m_intersectDist = closestDist;
    return closest;
}

