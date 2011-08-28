/******************************************************************************
 * lighting.h
 * Copyright 2011 Iain Peet
 *
 * Defines entities in the world which cast light on their surroundings.
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

#ifndef LIGHTING_H_
#define LIGHTING_H_

#include "image/colour.h"
#include "trace/geom.h"

class Ray;
class World;


/** Expresses a particular lighting condition.  Lighting
 *  has both intensity and direction */
class Lighting {
public:
    RayVector m_dir;
    RayColour m_intensity;

public:
    Lighting(): m_dir(), m_intensity() {}
    Lighting(const RayVector &dir, const RayColour &intensity):
        m_dir(dir), m_intensity(intensity)
        {}
    Lighting(const Lighting &other) :
        m_dir(other.m_dir), m_intensity(other.m_intensity)
        {}
};

#endif // LIGHTING_H_

