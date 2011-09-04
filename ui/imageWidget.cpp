/******************************************************************************
 * imageWidget.cpp
 * Copyright 2011 Iain Peet
 *
 * A Qt widget which draws a ray image.
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

#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <memory>

#include "imageWidget.h"

#include "image/image.h"
#include "trace/render.h"
#include "util/trace.h"

static trc_ctl_t imgWidgetTrace = {
    TRC_DFL_LVL,
    "IMG_WGT",
    TRC_STDOUT
};
#define TRACE(level, args...) \
    trc_printf(&imgWidgetTrace,level,1,args)

ImageWidget::ImageWidget(Image &img, QWidget * parent) :
    QWidget(parent),
    m_image(img.width(), img.height(), QImage::Format_ARGB32)
{ 
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    TRACE(TRC_INFO, "Created new ImageWidget, %dx%d\n", 
        m_image.width(), m_image.height());
    for(unsigned i=0; i<img.height(); ++i) {
        for(unsigned j=0; j<img.width(); ++j) {
            m_image.setPixel(j, i, toQColor(img, i, j).rgb());
        }
    }
}

ImageWidget::ImageWidget(Render &render, QWidget *parent) :
    QWidget(parent),
    m_image(render.m_processedSize.m_width, 
        render.m_processedSize.m_height, 
        QImage::Format_ARGB32)
{
    TRACE(TRC_INFO, "Created new ImageWidget, %dx%d\n", 
        m_image.width(), m_image.height());

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    std::auto_ptr<Image> img = render.execute();
    for(unsigned i=0; i<img->height(); ++i) {
        for(unsigned j=0; j<img->width(); ++j) {
            m_image.setPixel(j, i, toQColor(*img, i, j).rgb());
        }
    }
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    TRACE(TRC_DTL, "Painted ImageWidget\n");
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), m_image);
}

QColor ImageWidget::toQColor(Image &img, unsigned i, unsigned j) {
    return QColor(
            intColour(img.at(i,j,RED), 8),
            intColour(img.at(i,j,GREEN), 8),
            intColour(img.at(i,j,BLUE), 8) );
}

