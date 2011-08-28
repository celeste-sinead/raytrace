/******************************************************************************
 * ray.h
 * Copyright 2010 Iain Peet
 *
 * A Ray tracks a ray of light from some observation point back to its origin
 * in order to determine helpful things like color and intensity.  Once the
 * origin of a ray is found, it may be necessary to spawn one or several
 * child rays to determine the traits of the parent ray ( if this seems 
 * backwards, that's because it is.  The whole point of ray tracing is that
 * we're working backwards ) 
 *
 * A Ray is essentially a unit vector which wants nothing more from
 * the universe than to have a RayColour to call its own.
 *
 * For this project, the 'origin' of the ray is the point where its light
 * began travelling.  This is the point we are trying to find.  The 'endpoint'
 * of the ray is where the light was observed.  This is what we're tracking
 * back from.  The 'direction' points from the origin to the endpoint, which
 * is a bit awkward because this is the opposite of the direction we care
 * about mathematically, but it would be terribly inconsistent otherwise.
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

#ifndef ray_h_
#define ray_h_

#include <vector>
#include <tr1/memory>
#include "image/colour.h"
#include "geom.h"

class RayObject;

/** A Ray is used to find the origin of a ray of light, in order to
 *  figure out its colour.  The origin of the Ray might spawn children in
 *  order to determine the colour. (e.g for reflection).  
 *  When a RayObject determines that is the closest object to intersect this
 *  ray yet, it will record some information about itself in the Ray object
 *  so that we can contact it if it ends up being the closest intersecting
 *  object */
class Ray {
private:
    // Current ray hierarchy depth.
    int m_depth;
    std::vector<std::tr1::shared_ptr<Ray> > m_children;

private:
    // We would need to do a deep copy.  So, no copying!
    Ray(const Ray& other);
    Ray& operator=(const Ray& other);

public:  
    //! A unit vector with the direction of this Ray
    RayVector   m_dir; 
    //! The point where this ray is observed
    Coord       m_endpoint;
    //! Distance from endpoint to the first intersecting object
    double      m_intersectDist;
    //! The colour of this ray
    RayColour   m_colour;
    //! Maximum number of rays to create
    int         m_depthLimit;
    
    Ray(int depthLimit=0) : 
        m_depth(0), m_depthLimit(depthLimit)
        {}
    virtual ~Ray();

    /** Moves the endpoint of the ray a little bit along the ray.
     *  This is used to prevent double-detections for reflections, etc.
     *  @param distance  The distance to move the origin. */
    void nudge(double distance=1E-5);
	
    /** Create a child for this Ray, if possible.  
     *  @return The new child.  0 if creation fails (ie. we've reached the
     *          limit of the Ray hierarchy) */
    std::tr1::shared_ptr<Ray> createChild();
};

#endif // ray_h_

