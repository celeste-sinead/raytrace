/******************************************************************************
 * light_sources.h
 * Copyright 2011 Iain Peet
 *
 * Defines a few RayObjects which cast light on the scene.
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

#ifndef LIGHT_SOURCE_H_
#define LIGHT_SOURCE_H_

#include "trace/object.h"
#include "trace/sphere.h"

/** A simple point source of light. */
class PointSource : public InvisibleObject {
protected:
    RayColour m_intensity;
    RayVector m_origin;

public:
    PointSource(const RayVector &origin, const RayColour &intensity):
        m_intensity(intensity), m_origin(origin)
        {}

    virtual Lighting lightingAt(Coord &point, World &world);
};

/** A visible, spherical light source.  Acts as a point source, but
 *  is also visible for direct ray intersection */
class SphereSource: public BaseSphere, public PointSource {
public:
    SphereSource(const RayVector &origin, double radius, const RayColour &intensity):
        BaseSphere(origin, radius),
        PointSource(origin, intensity)
        {}

    virtual bool colour(Ray &inbound, World &world);

    virtual double intersectDist(Ray &inbound)
        { return BaseSphere::intersectDist(inbound); }
    virtual Lighting lightingAt(Coord &point, World &world)
        { return PointSource::lightingAt(point, world); }

};

#endif //LIGHT_SOURCE_H_
