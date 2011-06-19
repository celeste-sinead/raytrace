/*
 * Copyright 2009 Iain Peet
 * 
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
 */

/*
 * unit.h
 *
 * Provides macros used for a simple unit test framework.
 *
 * See unit-main.c for an example of how to uses these in code.
 */

#ifndef UNIT_H_
#define UNIT_H_

#include <stdio.h>

/** Test Definition Macros ***************************************************/

/**
 * @brief Begins a unit test function definition.
 * Expands to a function header and print out.
 * @param name	The identifier for the funcion.  (C function name)
 * @param title	A human readable test function name (C string)
 */
#define START_TEST_FN(name,title) \
	void name(int* _ut_passed, int* _ut_total) { \
		printf("Testing %s\n",title);
	 
/**
 * @brief Tests a condition.
 * Evaluates the given statement.  A nonzero result is interpreted as a 
 * successful test, 0 is an error.  Updates the number of successful and
 * the total number of tests in this function.  Can only be used
 * in a function defined using START_TEST_FN.
 * @param statement	The statement to evaluate
 * @param args...	A format string, followed by its arguments, which
 * 					should be printed after evaluating the statement.
 * 					The format string itself is required.
 */
#define TEST_CONDITION(statement,args...) \
	*_ut_total += 1; \
	if(statement) { \
		*_ut_passed += 1; \
		printf("[PASSED] "); \
	} else printf("[FAILED] "); \
	printf(args);
		
	
/**
 * @brief Ends a unit test function definition
 * Prints the results of the unit test funciton.
 */
// Ends a function definition
#define END_TEST_FN \
		printf("Finished. [%d/%d Successful]\n\n",*_ut_passed,*_ut_total);\
		return;\
	}

/** Text Execution Macros ****************************************************/

/**
 * @brief Begins unit testing code.
 * Prints a message and initializes variables used to track unit test 
 * results (at local scope).
 */
#define START_TEST_RUNNER \
	printf("*** Beginning unit test run ***\n\n");\
	int _cur_passed, _cur_total, _total_passed = 0, _total_total = 0;
	
/**
 * @brief Executes a unit test.
 * Calls the specified unit test function, updating the total tests
 * passed / executed.  The unit test function must be defined using the
 * START_TEST_FN macro.  The function name is declared in this expansion,
 * so it should not be declared explicitly.
 * @param name	The name of the test function.  Same as the 'name' parameter
 * 				to START_TEST_FN.  (C function nane)
 */
#define EXEC_TEST(name) \
	_cur_passed = _cur_total = 0; \
	void name(int*,int*);\
	name(&_cur_passed,&_cur_total);\
	_total_passed += _cur_passed;\
	_total_total += _cur_total;
	
/**
 * @brief Ends unit testing code.
 * Prints results of all unit test functions executed by EXEC_TEST
 */
// Ends a unit test run
#define END_TEST_RUNNER \
	printf("\n*** Finished unit test run ***\n");\
	printf("%d Passed\n",_total_passed);\
	printf("%d Total\n",_total_total); \
	if(_total_passed==_total_total) printf("All tests successful!\n"); \
	else printf("Tests failed.\n");

#endif //UNIT_H_