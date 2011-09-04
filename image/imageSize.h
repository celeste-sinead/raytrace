/******************************************************************************
 * imageSize.h
 * Copyright 2011 Iain Peet
 *
 * A simple class representing the size of an image (with + height)
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

#ifndef IMAGE_SIZE_H_
#define IMAGE_SIZE_H_

class ImageSize {
public:
    unsigned m_width;
    unsigned m_height;
    ImageSize(): m_width(0), m_height(0) {};
    ImageSize(unsigned width, unsigned height):
        m_width(width), m_height(height)
        {}
};

#endif //IMAGE_SIZE_H_
