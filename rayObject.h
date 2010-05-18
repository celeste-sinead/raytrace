/******************************************************************************
 * rayObject.h
 * Copyright 2010 Iain Peet
 *
 * Defines a raytracing object, which is any object which a ray might strike
 * and interact with.  The RayObject class provides infrastructure for managing
 * objects in the graphics universe.  It also provides the coarse intersect
 * detecttion, which allows us to check whether passes near an object very 
 * quickly.  Coarse intersect detection simply checks whether the ray passes
 * through a sphere containing the object (this is easy).
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

#ifndef ray_object_h_
#define ray_object_h_

#include "geom.h"

class Ray;
class World;

/** Base class for all elements in the graphics universe which can intersect
 *  with rays.  Provides bookkeeping infrastructure and coarse ray intersect
 *  detection.
 *  This class needs to be re-entrant during the rendering phase.  Multiple 
 *  worker threads should be able to use this class when tracing their rays
 *  without locking or races. */
class RayObject {
protected:
    //! Origin of this object. Center of a circumscribing sphere. 
    Coord     m_origin;
    /** Radius of a sphere about the origin which contains this object.
     *  Intersection will not work if this is too small.  Too big will work,
     *  though this will mean unnecessary fine intersect checks */
    double    m_radius;

public:
    RayObject() : 
        m_origin(),m_radius(0.0)
        {}
    RayObject(const Coord &origin, double radius) :
        m_origin(origin), m_radius(radius)
        {}

    /** Check if a ray intersects with this object.  A coarse check is made 
     *  to see if intersection can be ruled out quickly.  If the coarse check
     *  show intersection is plausible, a fine check (provided by subclass) is
     *  run to determine if the ray actually intersects.
     *  This function is re-entrant.
     *  @param inbound  The ray to check for intersection.
     *  @return         true if inbound intersects. false otherwise */
    bool intersects(Ray *inbound);

    /** Determines the colour of a colliding ray.
     *  @param inbound  The ray to colour.  Behaviour is undefined if this is 
     *                  a non-intersecting ray.  (collides(inbound)==false) */
    virtual bool colour(Ray *inbound, World *world) = 0;
    
    const Coord& origin() const
        {return m_origin;}

protected:
    /** Accurately determines whether a ray intersects this object.
     *  This is called by intersects() if coarse checks indicate the ray 
     *  may intersect this object.  This function should, however, be valid
     *  for any possible ray.
     *  This function is expected to calculate the distance between the
     *  point of intersection and the ray's origin, and record this information
     *  in the Ray so that other RayObjects can determine if they are obscured
     *  by this object. 
     *  @param inbound  The ray to check for intersection.
     *  @return         true if inbound intersects.  false otherwise. */
    virtual bool intersectsFine(Ray *inbound) = 0;

};

#endif // ray_object_h_

