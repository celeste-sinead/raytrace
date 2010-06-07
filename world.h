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

class RayObject;
class Ray;

/** A simple list of objects which may appear in a raytraced image.
 *  ( Could just use a std::vector right now, but I plan to add 
 *    extra features to speed up searches, so it's its own class */
class World {
private:
    std::vector<RayObject*>  m_objects;
    
public:
    //! Colour returned when a ray trace fails
    RayColour                m_defaultColour;
    //! Colour of rays which hit no objects
    RayColour                m_backgroundColour;
  
    /** Trace a ray.
     *  @param ray  The ray to trace.
     *              The final colour of the ray will be stored in ray->m_colour
     *  @return true if the trace succeeds
     *          false if the trace fails, (e.g. too many reflections) */
    bool trace(Ray *ray);
   
    /** RayObject list accessors / modifiers */
    int size()
        { return m_objects.size(); }
    void push_back(RayObject *obj)
        { m_objects.push_back(obj); }
    RayObject * remove(int index);
    RayObject *& at(int index)
        { return m_objects[index]; }
    RayObject *& operator[](int index)
        { return at(index); }
};

#endif //world_h_