/******************************************************************************
 * ray.cpp
 * Copyright 2010 Iain Peet
 *
 * Implements a class tracking light back from an endpoint.
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

#include "ray.h"

Ray::~Ray()
{
    for(unsigned i=0; i<m_children.size(); ++i) 
        delete m_children[i];
}

//! Allocate a new Ray, if we haven't reached limit of the hierarchy
Ray* Ray::createParent()
{
    if( m_depth >= m_depthLimit ) return 0;

    Ray * newParent = new Ray(m_depthLimit);
    if( !newParent ) return 0;

    newParent->m_depth = m_depth + 1;

    m_children.push_back(newParent);
    return newParent;
}

//! Moves the origin of the ray a little bit.
void Ray::nudge(double distance)
{
    m_endpoint = m_endpoint + distance * m_dir;
}

