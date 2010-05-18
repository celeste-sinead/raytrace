/******************************************************************************
* view.h
* Copyright 2010 Iain Peet
*
* Provides RayView classes, which trace a number of rays to render an image.
* Also provides the ViewObjectList class, which maintains a list of objects
* which might be seen in a RayView.
******************************************************************************
* This program is distrib
    $(COMMON_OBJS) \uted under the of the GNU Lesser Public License. 
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

#ifndef view_h_
#define view_h_

#include <vector>

#include "geom.h"
#include "colour.h"

class RayObject;
class RayImage;
class Ray;
class World;

/** The RayView class interface. */
class RayView {
public:
    virtual void render(RayImage *image, World *world) = 0;
};

/** A simple RayView implementation, which traces a number of parallel rays
 *  originating from points on a rectangle in space */
class ParallelView: public RayView {
public:
    /** View window geometry. 
     *  m_origin is the co-ordinate of the top-left corner of the view.
     *  m_xVec points in the image's 'right' direction
     *  m_yVec points in the image's 'down' direction
     *  Rays are cast in the direction of the cross of m_xVec with m_yVec */
    Coord       m_origin;
    RayVector   m_xVec;
    RayVector   m_yVec;
  
    virtual void render(RayImage *image, World *world);
};

#endif //view_h_