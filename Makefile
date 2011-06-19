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

# List of root-level cpp sources:
CXX_SRCS:=$(CXX_SRCS) $(wildcard *.cpp)

# Compile config
CXX= g++
MOC= moc-qt4
CXXFLAGS= -Wall -g -O0
INCLUDES= -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4

# Include all the subdirs
include $(patsubst %,%/Makefile,$(SUBDIRS))

# Generated directories
GENDIR:=gen

# Deps need to be kept separately, because compilation of other
# files will change dep dir access times, and deps must depend
# explicitly on deps dir in order for implicit creation by
# makefile to work.
DEPDIR:=dep

# All output dirs, which may need to be created, in the order
# they need to be created.
DEP_DIRS:=$(DEPDIR) $(patsubst %,$(DEPDIR)/%,$(SUBDIRS))
OUTPUT_DIRS:=$(GENDIR)\
			 $(DEP_DIRS)\
			 $(patsubst %,$(GENDIR)/%,$(SUBDIRS)) \

$(OUTPUT_DIRS): ; mkdir $@

# Compilation of cpp objects
CXX_OBJS:=$(patsubst %.cpp,$(GENDIR)/%.o,$(CXX_SRCS))
$(CXX_OBJS): $$(patsubst $(GENDIR)/%.o,%.cpp,$$@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -c -o $@

# .cpp dependency generation
CXX_DEPS:=$(patsubst %.cpp,$(DEPDIR)/%.d,$(CXX_SRCS))
$(CXX_DEPS): $$(patsubst $(DEPDIR)/%.d,%.cpp,$$@) $(DEP_DIRS)
	$(CXX) $(INCLUDES) -MM -MT $(<:%.cpp=$(DEPDIR)/%.o) -MF $@ $<
depends: $(OUTPUT_DIR) $(CXX_DEPS)
include $(CXX_DEPS)

# QT MOC generation
QT_MOC_SRCS:=$(patsubst %.h,$(GENDIR)/%.moc.cpp,$(QT_HEADS))
$(QT_MOC_SRCS): $$(patsubst $(GENDIR)/%.moc.cpp,%.h,$$@)
	$(MOC) $< -o $@

QT_MOC_OBJS:=$(patsubst %.cpp,%.o,$(QT_MOC_SRCS))
$(QT_MOC_OBJS): $$(patsubst %.o,%.cpp,$$@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -c -o $@

all: $(OUTPUT_DIRS) $(CXX_OBJS) $(QT_MOC_OBJS)

clean:
	rm -rf $(GENDIR)
	rm -rf $(DEPDIR)

debugp:
	@echo "CXX_SRCS: $(CXX_SRCS)"
	@echo "CXX_OBJS: $(CXX_OBJS)"
	@echo "QT_HEADS: $(QT_HEADS)"
	@echo "QT_MOC_SRCS: $(QT_MOC_SRCS)"
	@echo "QT_MOC_OBJS: $(QT_MOC_OBJS)"

