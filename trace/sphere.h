/******************************************************************************
 * sphere.h
 * Copyright 2011 Iain Peet
 *
 * Provides spherical objects.
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

#ifndef SPHERE_H_
#define SPHERE_H_

#include "trace/object.h"
#include "trace/geom.h"
#include "image/colour.h"

class Ray;

/** Object providing methods for computing ray/sphere intersections.
 *  In addition to being useful for spherical objects, these methods
 *  are useful for coarse intersection checks for more complex
 *  objects which can be circumscribed by a sphere */
class BaseSphere : public NonLightingObject {
protected:
    //! Origin of this object. Center of a circumscribing sphere. 
    Coord     m_origin;
    /** Radius of a sphere about the origin which contains this object.
     *  Intersection will not work if this is too small.  Too big will work,
     *  though this will mean unnecessary fine intersect checks */
    double    m_radius;

protected:
    RayVector normal(const Coord &point);

public:
    BaseSphere(const Coord& origin, double radius) : 
        m_origin(origin), m_radius(radius)
        {}

    void setOrigin(const Coord& newOrig) { m_origin = newOrig; }
    void setRadius(double newRad) { m_radius = newRad; }

    virtual double intersectDist(Ray &inbound);
};

/** A solid sphere */
class Sphere : public BaseSphere {
public:
    //! The gains this object applies to incident light, in all directions.
    RayColour m_diffusivity;
    //! The gains this object applies to reflected light
    RayColour  m_reflectivity;

public:
    Sphere(const Coord& origin, 
           double radius, 
           const RayColour& diffusivity = RayColour(0,0,0),
           const RayColour& reflectivity = RayColour(0,0,0)
        ) :
        BaseSphere(origin, radius),
        m_diffusivity(diffusivity),
        m_reflectivity(reflectivity)
        {}

    virtual bool colour(Ray &inbound, World &world);
};

#endif //SPHERE_H_
