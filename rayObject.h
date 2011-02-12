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

#include "geom.h"
#include "colour.h"

class Ray;
class World;

/** Abstract base for any objects which may be intersected by a ray. */
class RayObject {
public:
    /** Determine the distance from the ray's origin to the
     *  (nearest) intersection of the ray with this object 
     *  @param inbound The ray whose interesect distance is reauired. 
     *  @return        The intersect distance, if the ray intersects.
     *                 -1.0 If the ray does not intersect. */
    virtual double intersectDist(Ray *inbound) = 0;

   
    /* Determine the colour of a given ray.
     * @param inbound The ray to colour.
     * @param world   The world in which this object exists.  
     * @return        true if inbound intersects and has been coloured.
     *                false if inbound does not actually intersect */
    virtual bool colour(Ray *inbound, World *world) = 0;
};


/** Object providing methods for computing ray/sphere intersections.
 *  In addition to being useful for spherical objects, these methods
 *  are useful for coarse intersection checks for more complex
 *  objects which can be circumscribed by a sphere */
class BaseSphere : public RayObject {
protected:
    //! Origin of this object. Center of a circumscribing sphere. 
    Coord     m_origin;
    /** Radius of a sphere about the origin which contains this object.
     *  Intersection will not work if this is too small.  Too big will work,
     *  though this will mean unnecessary fine intersect checks */
    double    m_radius;

protected:
    Coord intersectPoint(Ray* ray);
    RayVector normal(const Coord &point);
    double sphereIntersectDist(Ray* ray);

public:
    BaseSphere(const Coord& origin, double radius) : 
        m_origin(origin), m_radius(radius)
        {}

    void setOrigin(const Coord& newOrig) { m_origin = newOrig; }
    void setRadius(double newRad) { m_radius = newRad; }
};

/** A solid sphere */
class Sphere : public BaseSphere {
private:
    RayColour m_reflectivity;

public:
    Sphere(const Coord& origin, double radius, const RayColour& reflectivity):
        BaseSphere(origin, radius), m_reflectivity(reflectivity)
        {}

    void setReflectivity(const RayColour& newRef) { m_reflectivity = newRef; }

    virtual double intersectDist(Ray* inbound)
        { return sphereIntersectDist(inbound); }
    virtual bool colour(Ray* inbound, World* world);
};

#endif // ray_object_h_

