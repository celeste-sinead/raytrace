/******************************************************************************
 * sphere.h
 * Copyright 2010 Iain Peet
 *
 * A RayObject which is a simple, spherical solid.
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

#ifndef sphere_h_
#define sphere_h_

#include "rayObject.h"

class Sphere : public RayObject {
public:
    Sphere() : RayObject() 
        {}
    Sphere(const Coord& origin, double radius) : RayObject(origin,radius) 
        {}
	
    virtual void colour(Ray & inbound);
	
protected:
    
    virtual bool intersectsFine(Ray & inbound);
};

#endif // sphere_h_
