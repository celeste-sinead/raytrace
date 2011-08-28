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
#include <memory>
#include <iostream>

#include "file/reader.h"
#include "image/colour.h"
#include "image/image.h"
#include "image/pipeline.h"
#include "image/rayImage.h"
#include "image/resample.h"
#include "trace/lighting.h"
#include "trace/light_sources.h"
#include "trace/object.h"
#include "trace/sphere.h"
#include "trace/view.h"
#include "trace/world.h"
#include "ui/imageWidget.h"

using namespace std;

void qtTest(QApplication &app);

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    qtTest(app);
}
    
void qtTest(QApplication &app) {
    SceneReader r ("examples/scene1.json");
    if (!r.parse()) {
        cerr << "Failed to parse scene" << endl;
        cerr << r.getErrors() << endl;
        return;
    }

    World world;
    world.m_defaultColour.set(0,1.0,0);  
    world.m_globalDiffuse.set(0.05, 0.05, 0.15); 
    
    auto_ptr<RayObject> sph (
        new Sphere( Coord(0,0,0), 1.0, 
             RayColour(0.1, 0.25, 1.0),
             RayColour(0.1,0.25,1.0)));
    world.addObject(sph);

    auto_ptr<RayObject> sph2 ( 
        new Sphere( Coord(0.5,1.5,1.5), 1.5, 
             RayColour(1.0, 1.0, 0.1),
             RayColour(1.0, 1.0, 0.2)));
    world.addObject(sph2);

    auto_ptr<RayObject> sph3 (
        new Sphere(Coord(0,-1.25, 0), 0.5, 
             RayColour(0.1, 1.0, 0.1), 
             RayColour(0.2, 1.0, 0.2)));
    world.addObject(sph3);

    auto_ptr<RayObject> sph4 (
        new Sphere( Coord(1.2,0.3,0.1), 0.75, 
             RayColour(1.0, 0.1, 0.1), 
             RayColour(1.0, 0.2, 0.2)));
    world.addObject(sph4);

    auto_ptr<RayObject> sph5 (
        new Sphere( Coord(-3.5,-2, 2), 3,
             RayColour(0, 0, 0.4),
             RayColour(1, 1, 1)));
    world.addObject(sph5);

    auto_ptr<RayObject> light1 (
        new SphereSource(RayVector(1.5,-2.5,1.5), 0.125, RayColour(90.0,90.0,90.0)));
    world.addObject(light1);

    auto_ptr<RayObject> light2 (
        new SphereSource(RayVector(5,-1,-1), 0.125, RayColour(100,100,100)));
    world.addObject(light2);
    
    ParallelView view;
    view.m_origin = Coord(2.0,-2,2);
    view.m_xVec = RayVector(0,4.5,0);
    view.m_yVec = RayVector(0,0,-3);
    
    RayImage traced (300, 200);

    view.render(&traced, &world, 20);

    ImagePipeline p;
    p.push(auto_ptr<ImageTransform>(new LogHDRToDisplay(0.0, 0.5)));
    p.setResampler(auto_ptr<Resampler>(new BilinearInterpolator()));

    ImageWidget *oiw = new ImageWidget(
        *(p.process(traced, 1200, 800).release()));

    QHBoxLayout *imgs = new QHBoxLayout();
        imgs->addWidget(oiw);

    QWidget *topWidget = new QWidget();
    topWidget->setLayout(imgs);
    topWidget->show();

    app.exec();
}


