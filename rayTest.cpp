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
    world.m_globalDiffuse.set(0.01,0.01,0.01); // white
    
    Sphere sph ( Coord(0,0,0), 1.0, RayColour(100,100,100) );
    world.push_back(&sph);
    
    ParallelView view;
    view.m_origin = Coord(2,-1.5,1.5);
    view.m_xVec = RayVector(0,3,0);
    view.m_yVec = RayVector(0,0,-3);
    
    RayImage image (w, h);
    
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
    world.m_globalDiffuse.set(0.05, 0.05, 0.15); // dark blue 
    
    Sphere sph ( Coord(0,0,0), 1.0, RayColour(0.0, 0.6, 1.0) );
    world.push_back(&sph);

    Sphere sph2 ( Coord(1,1,1), 0.5, RayColour(0.8, 0.0, 0.4) );
    world.push_back(&sph2);

    Sphere sph3 ( Coord(0,-1, 0), 0.5, RayColour(0.0, 0.8, 0.0) );
    world.push_back(&sph3);
    
    ParallelView view;
    view.m_origin = Coord(2,-1.5,1.5);
    view.m_xVec = RayVector(0,3,0);
    view.m_yVec = RayVector(0,0,-3);
    
    RayImage image (w, h);

    view.render(&image, &world);

    DisplayImageQt *depthImage = new DisplayImageQt(w, h, Qt::blue);
    DepthAdapter depth (2.0);
    depthImage->fromRay(&image, &depth);

    DisplayImageQt *visImage = new DisplayImageQt(w, h, Qt::blue);
    LinearColourAdapter colour (&image);
    visImage->fromRay(&image, &colour);

    QHBoxLayout *imgs = new QHBoxLayout();
    imgs->addWidget(depthImage);
    imgs->addWidget(visImage);

    QWidget *topWidget = new QWidget();
    topWidget->setLayout(imgs);
    topWidget->show();

    app.exec();
}
