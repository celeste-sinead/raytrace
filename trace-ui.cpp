/******************************************************************************
 * ui.cpp
 * Copyright 2011 Iain Peet
 *
 * Provides a GUI for looking at traced images.
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

#include <QtGui>

#include "image/image.h"
#include "trace/lighting.h"
#include "trace/rayObject.h"
#include "trace/view.h"
#include "trace/world.h"
#include "ui/imageWidget.h"

void qtTest(QApplication &app);

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    qtTest(app);
}
    
void qtTest(QApplication &app) {
    const int w = 1500;
    const int h = 1000;

    World world;
    world.m_defaultColour.set(0,1.0,0);  
    world.m_globalDiffuse.set(0.05, 0.05, 0.15); 
    
    Sphere sph ( Coord(0,0,0), 1.0, 
                 RayColour(0.1, 0.25, 1.0),
                 RayColour(0.1,0.25,1.0) );
    world.addObject(&sph);

    Sphere sph2 ( Coord(0.5,1.5,1.5), 1.5, 
                  RayColour(1.0, 1.0, 0.1),
                  RayColour(1.0, 1.0, 0.2) );
    world.addObject(&sph2);

    Sphere sph3 ( Coord(0,-1.25, 0), 0.5, 
                  RayColour(0.1, 1.0, 0.1), 
                  RayColour(0.2, 1.0, 0.2) );
    world.addObject(&sph3);

    Sphere sph4( Coord(1.2,0.3,0.1), 0.75, 
                 RayColour(1.0, 0.1, 0.1), 
                 RayColour(1.0, 0.2, 0.2) );
    world.addObject(&sph4);

    Sphere sph5( Coord(-3.5,-2, 2), 3,
                 RayColour(0, 0, 0.4),
                 RayColour(1, 1, 1) );
    world.addObject(&sph5);

    SphereSource light1 (RayVector(1.5,-2.5,1.5), 0.125, RayColour(90.0,90.0,90.0));
    world.addLight(&light1);
    world.addObject(&light1);

    SphereSource light2 (RayVector(5,-1,-1), 0.125, RayColour(100,100,100));
    world.addLight(&light2);
    world.addObject(&light2);
    
    ParallelView view;
    view.m_origin = Coord(2.0,-2,2);
    view.m_xVec = RayVector(0,4.5,0);
    view.m_yVec = RayVector(0,0,-3);
    
    RayImage image (h, w);

    view.render(&image, &world, 20);

    RayColourImage      rcimg(image);
    LinearColourAdapter colour(0.0,1.0);
    DisplayImage        dimg(rcimg, colour);
    ImageWidget *visImage = new ImageWidget(&dimg);

    QHBoxLayout *imgs = new QHBoxLayout();
    imgs->addWidget(visImage);

    QWidget *topWidget = new QWidget();
    topWidget->setLayout(imgs);
    topWidget->show();

    app.exec();
}


