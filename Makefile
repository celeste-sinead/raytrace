#  Makefile
#  Copyright 2011 Iain Peet
# 
#  Root makefile.  Includes subdir makefiles to get a complete list of
#  available sources; generates deps and objects for those sources, 
#  and compiles binaries from the objects.
# 
#  This program is distributed under the of the GNU Lesser Public License. 
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

.DEFAULT_GOAL=all
.SECONDEXPANSION:

# List of subdir from which to obtain source lists
SUBDIRS:=image\
		 trace\
		 util

# Compile config
CXX= g++
CXXFLAGS= -Wall -g -O0
INCLUDES= -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4

# Include all the subdirs
include $(patsubst %,%/Makefile,$(SUBDIRS))

OBJDIR:=obj

# All output dirs, which may need to be created, in the order
# they need to be created.
OUTPUT_DIRS:=$(OBJDIR)\
			 $(patsubst %,$(OBJDIR)/%,$(SUBDIRS))

$(OUTPUT_DIRS): ; mkdir $@

# Compilation of cpp objects
CXX_OBJS:=$(patsubst %.cpp,$(OBJDIR)/%.o,$(CXX_SRCS))
$(CXX_OBJS): $$(patsubst $(OBJDIR)/%.o,%.cpp,$$@) $(OUTPUT_DIRS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -c -o $@

all: $(OUTPUT_DIRS) $(CXX_OBJS)

clean:
	rm -rf $(OBJDIR)

debugp:
	@echo "CXX_SRCS: $(CXX_SRCS)"
	@echo "CXX_OBJS: $(CXX_OBJS)"

