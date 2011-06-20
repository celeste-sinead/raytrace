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

#include "imageWidget.h"

#include "image/image.h"
#include "util/trace.h"

static trc_ctl_t imgWidgetTrace = {
    TRC_DFL_LVL,
    "IMG_WGT",
    TRC_STDOUT
};
#define TRACE(level, args...) \
    trc_printf(&imgWidgetTrace,level,1,args)

ImageWidget::ImageWidget(DisplayImage *img, QWidget * parent) :
    QWidget(parent),
    m_image(img->width(), img->height(), QImage::Format_ARGB32)
{ 
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    TRACE(TRC_INFO, "Created new ImageWidget, %dx%d\n", 
        m_image.width(), m_image.height());
    QColor curC;
    for(int i=0; i<img->height(); ++i) {
        for(int j=0; j<img->width(); ++j) {
            curC = QColor(img->at(i,j).red(8),
                           img->at(i,j).green(8),
                           img->at(i,j).blue(8));
            m_image.setPixel(j, i, curC.rgb());
        }
    }
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    TRACE(TRC_DTL, "Painted ImageWidget\n");
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), m_image);
}

