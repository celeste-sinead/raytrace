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
#include "rayObject.h"
#include "view.h"
#include "world.h"

#include <QtGui>

void singleSphere();
void qtTest(QApplication &app);

int main(int argc, char *argv[]) {
    /** Run unit tests */
    START_TEST_RUNNER;
    
    EXEC_TEST(sphere_intersect);
    EXEC_TEST(vector_geom);
    
    END_TEST_RUNNER;
    
    printf("Ascii Render:\n"); 
    singleSphere();

    QApplication app(argc, argv);
    qtTest(app);
    
    printf("Done!\n");
    return 0;   
}

void singleSphere() {
    const int w = 8;
    const int h = 4;

    World world;
    world.m_defaultColour.set(1.0,0,0);  // bright red
    world.m_backgroundColour.set(0,0,0); // black
    
    Sphere sph ( Coord(0,0,0), 1.0, RayColour(1.0,1.0,1.0) );
    world.push_back(&sph);
    
    ParallelView view;
    view.m_origin = Coord(2,-1.5,1.5);
    view.m_xVec = RayVector(0,3,0);
    view.m_yVec = RayVector(0,0,-3);
    
    RayColour fill (0,0,1);
    RayImage image (w, h, &fill);
    
    view.render(&image, &world);
    
    AsciiImage ascii(w, h);
    ascii.fromRay(&image,0,0.5);
    ascii.print();

}

void qtTest(QApplication &app) {
    const int w = 512;
    const int h = 512;

    World world;
    world.m_defaultColour.set(1.0,0,0);  // bright red
    world.m_backgroundColour.set(0,0,0); // black
    
    Sphere sph ( Coord(0,0,0), 1.0, RayColour(0.0, 0.6, 1.0) );
    world.push_back(&sph);
    
    ParallelView view;
    view.m_origin = Coord(2,-1.5,1.5);
    view.m_xVec = RayVector(0,3,0);
    view.m_yVec = RayVector(0,0,-3);
    
    RayColour fill (0,0,1);
    RayImage image (w, h, &fill);

    view.render(&image, &world);

    DisplayImageQt qtImage (w, h, Qt::blue);
    LinearColourAdapter adapter (1.0);
    qtImage.fromRay(&image, &adapter);
    qtImage.show();
    app.exec();
}
