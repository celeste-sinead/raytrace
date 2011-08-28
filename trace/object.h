/******************************************************************************
 * rayObject.h
 * Copyright 2010 Iain Peet
 *
 * Defines the bases of entities which 'exist' in the raytraced universe. 
 * Currently, these objects consist of RayObjects and LightSources
 *
 * RayObjects are entities that can intersect and colour Rays.
 *
 * LightSources cannot directly interact with rays, but make some contribution
 * to the intensity of light at any given point in the world.
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

#include "image/colour.h"
#include "trace/geom.h"
#include "trace/lighting.h"

class Ray;
class World;

/** Abstract base for any objects within the world which effect
 *  tracing.  Object encompass both visible, physical objects and
 *  objects which affect lighting conditions. */
class RayObject {
public:
    /** Determine this object's contribution to lighting at a 
     *  given point in the world.
     *  @param  point The point where lighting should be evaluated 
     *  @return The intensity of light at the point */
    virtual Lighting lightingAt(Coord &point, World &world) = 0;

    /** Determine the distance from the ray's origin to the
     *  (nearest) intersection of the ray with this object 
     *  @param inbound The ray whose interesect distance is reauired. 
     *  @return        The intersect distance, if the ray intersects.
     *                 -1.0 If the ray does not intersect. */
    virtual double intersectDist(Ray &inbound) = 0;

   
    /* Determine the colour of a given ray.
     * @param inbound The ray to colour.
     * @param world   The world in which this object exists.  
     * @return        true if inbound intersects and has been coloured.
     *                false if inbound does not actally intersect */
    virtual bool colour(Ray &inbound, World &world) = 0;
};

/** Object which does not produce light. */
class NonLightingObject: public RayObject {
public:
    virtual Lighting lightingAt(Coord &point, World &world) {
        return Lighting();
    }
};

/** Object which cannot intersect rays. */
class InvisibleObject: public RayObject {
public:
    virtual double intersectDist(Ray &inbound) { return -1; }
    virtual bool   colour(Ray &inbound, World &world) { return true; }
};

#endif // ray_object_h_

