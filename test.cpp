/******************************************************************************
* rayTest.cpp
* Copyright 2010 Iain Peet
*
* Test entry point.
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

#include <cstdio>
#include <cstring>

#include "image/image.h"
#include "trace/rayObject.h"
#include "trace/view.h"
#include "trace/world.h"
#include "util/unit.h"

void singleSphere();

int main(int argc, char *argv[]) {
    /** Run unit tests */
    START_TEST_RUNNER;
    
    EXEC_TEST(sphere_intersect);
    EXEC_TEST(vector_geom);
    
    END_TEST_RUNNER;
    
    printf("Ascii Render:\n"); 
    singleSphere();

    printf("Done!\n");
    return 0;   
}

void singleSphere() {
    const int w = 8;
    const int h = 4;

    World world;
    world.m_defaultColour.set(1.0,0,0);  // bright red
    world.m_globalDiffuse.set(0.01,0.01,0.01); // white
    
    Sphere sph ( Coord(0,0,0), 1.0, RayColour(100,100,100) );
    world.addObject(&sph);
    
    ParallelView view;
    view.m_origin = Coord(2,-1.5,1.5);
    view.m_xVec = RayVector(0,3,0);
    view.m_yVec = RayVector(0,0,-3);
    
    RayImage image (h, w);
    
    view.render(&image, &world);
    
    AsciiImage ascii(h, w);
    ascii.fromRay(&image,0,0.5);
    ascii.print();

}

