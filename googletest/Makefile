#  Makefile
#  Copyright 2011 Iain Peet
# 
#  This is intended to be included by the root makefile.  Its purpose
#  is to provide a manifest of the source files available in this
#  directory.
# 
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>

# This gets the dir path that the including makefile used for this
# makefile.  This same path should be used for this folders sources.
# NB: immediate substitution is important, since MAKEFILE_LIST is volatile.
GTEST_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))

# Sources from googletest/src to be included in the test compilation
GTEST_SRCS:= gtest-all.cc

# Prepend the current directory name
GTEST_SRCS:= $(patsubst %,$(GTEST_DIR)googletest/src/%,$(GTEST_SRCS))

# Rule for getting googletest from svn
$(GTEST_SRCS):
	svn co http://googletest.googlecode.com/svn/trunk $(GTEST_DIR)googletest

# Rule for getting googletest headers from svn
$(GTEST_DIR)googletest/include/gtest/%.h: fetch_gtest
	svn co http://googletest.googlecode.com/svn/trunk $(GTEST_DIR)googletest

