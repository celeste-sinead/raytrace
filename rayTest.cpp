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

#include <iputil/unit.h>

int main() {
    /** Run unit tests */
    START_TEST_RUNNER;
    
    EXEC_TEST(sphere_intersect);
    
    END_TEST_RUNNER;
    
    /** Execute subjective / interactive / arbitrary tests */
    // nothing here yet
    return 0;   
}