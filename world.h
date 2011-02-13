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

#ifndef world_h_
#define world_h_

#include <vector>

#include "colour.h"

class LightSource;
class Ray;
class RayObject;

/** A simple list of objects which may appear in a raytraced image.
 *  ( Could just use a std::vector right now, but I plan to add 
 *    extra features to speed up searches, so it's its own class */
class World {
private:
    std::vector<RayObject*>   m_objects;
    std::vector<LightSource*> m_lights;
    
public:
    //! Colour returned when a ray trace fails
    RayColour                m_defaultColour;
    /** Diffuse light experienced by all objects.  This is also the background
     *  colour that is set to any non-intersecting rays */
    RayColour                m_globalDiffuse;
  
    /** Trace a ray.
     *  @param ray  The ray to trace.
     *              The final colour of the ray will be stored in ray->m_colour
     *  @return true if the trace succeeds
     *          false if the trace fails, (e.g. too many reflections) */
    bool trace(Ray *ray);

    /** Determine which object a ray first intersects, but do not colour
     *  or continue tracing 
     *  @param ray The ray for which to find an intersect.
     *             Intersect distance will be set if an intersect is found.
     *  @return    The first object intersecting the ray. 
     *             null if no objects intersect. */
    RayObject * intersect(Ray *ray);
   
    /** RayObject list accessors / modifiers */
    int size()
        { return m_objects.size(); }
    void addObject(RayObject *obj)
        { m_objects.push_back(obj); }
    RayObject * remove(int index);
    RayObject *& at(int index)
        { return m_objects[index]; }
    RayObject *& operator[](int index)
        { return at(index); }

    /** LightSource list accessors / modifiers */
    int numLights() 
        { return m_lights.size(); }
    void addLight(LightSource *light) 
        { m_lights.push_back(light); }
    const std::vector<LightSource*> & lights()
        { return m_lights; }
};

#endif //world_h_
