/******************************************************************************
 * imageWidget.h
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

#ifndef IMAGE_WIDGET_H_
#define IMAGE_WIDGET_H_

#include <QWidget>
#include <QImage>
#include <QColor>

class Image;

class ImageWidget : public QWidget { 
Q_OBJECT
private:
    QImage m_image;

    QColor toQColor(Image &img, unsigned i, unsigned j);

protected:
    void paintEvent(QPaintEvent *event);

public:
    ImageWidget(Image &img, QWidget *parent = 0);

    virtual QSize sizeHint() const 
        { return m_image.size(); }
};

#endif //IMAGE_WIDGET_H_

