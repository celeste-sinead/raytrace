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
#include <iputil/unit.h>

#include "colour.h"
#include "image.h"
#include "ray.h"
#include "sphere.h"
#include "view.h"
#include "world.h"

void single_sphere();

int main(int argc, char *argv[]) {
    /** Run unit tests */
    START_TEST_RUNNER;
    
    EXEC_TEST(sphere_intersect);
    EXEC_TEST(vector_geom);
    
    END_TEST_RUNNER;
    
    /** Execute subjective / interactive / arbitrary tests */
    // break out if we're not running interactive tests
    if( argc <= 1 || strncmp(argv[1],"interactive",11) ) return 0;
    printf("\nRunning interactive tests...\n");
    
    single_sphere();
    
    printf("Done!\n");
    return 0;   
}

void single_sphere() {
    World world;
    world.m_defaultColour.set(1.0,0,0);  // bright red
    world.m_backgroundColour.set(0,0,0); // black
    
    Sphere sph ( Coord(0,0,0), 1.0 );
    world.push_back(&sph);
    
    ParallelView view;
    view.m_origin = Coord(2,-1,1);
    view.m_xVec = RayVector(0,2,0);
    view.m_yVec = RayVector(0,0,-2);
    
    RayColour fill (0,0,1);
    RayImage image (6,6,&fill);
    
    view.render(&image, &world);
}
