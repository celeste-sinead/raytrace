/******************************************************************************
* rayTest.cpp
* Copyright 2010 Iain Peet
*
* Test entry point.
******************************************************************************/

#include <iputil/unit.h>

int main() {
    START_TEST_RUNNER;
    
    EXEC_TEST(sphere_intersect);
    
    END_TEST_RUNNER;
    return 0;   
}