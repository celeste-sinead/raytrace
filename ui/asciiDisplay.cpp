/******************************************************************************
 * asciiImage.cpp
 * Copyright 2011 Iain Peet
 *
 * Displays an Image, thresholded to binary, with boolean ASCII.
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

#include "asciiDisplay.h"

#include "image/image.h"

void displayAscii(Image& img, double threshold) {
    for (unsigned i=0; i<img.height(); ++i) {
        for (unsigned j=0; j<img.width(); ++j) {
            double sum = 0;
            for (unsigned k=0; k<img.colours(); ++k) {
                sum += img.at(i,j,k);
            }
            printf(sum >= threshold ? "X" : " ");
        }
        printf("\n");
    }
}

