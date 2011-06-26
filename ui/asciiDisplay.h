/******************************************************************************
 * asciiImage.h
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

#ifndef ASCII_DISPLAY_H_
#define ASCII_DISPLAY_H_

class Image;

/* Prints the image in ascii, placing empty spaces where
 * the intensity is less than the threshold, and Xs elsewhere*/
void displayAscii(Image& img, double threshold);

#endif //ASCII_DISPLAY_H_

