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
SRCDIRS:=image\
		 trace\
		 ui \
		 util

# List of root-level cpp sources:
CXX_SRCS:=$(CXX_SRCS)\
		  test.cpp \
		  trace-ui.cpp

# Include all the subdirs
include $(patsubst %,%/Makefile,$(SRCDIRS))

# Generated directories
GENDIR:=gen

# List of bins to link
BINS:=test trace-ui

COMMON_OBJS:= \
	$(patsubst %.cpp,$(GENDIR)/%.o,$(IMAGE_CXX_SRCS)) \
	$(patsubst %.cpp,$(GENDIR)/%.o,$(TRACE_CXX_SRCS)) \
	$(patsubst %.cpp,$(GENDIR)/%.o,$(UTIL_CXX_SRCS)) 

test_OBJS:= \
	$(COMMON_OBJS) \
    gen/ui/asciiDisplay.o \
	gen/test.o

trace-ui_OBJS:= \
	$(COMMON_OBJS) \
    gen/ui/imageWidget.o \
	gen/ui/imageWidget.moc.o \
	gen/trace-ui.o

# Compile config
CXX:= g++
MOC:= moc-qt4
CXXFLAGS:= -Wall -g -O0
INCLUDES:= -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4
LDFLAGS:= $(CXXFLAGS)
LIBS:= -lm -lQtGui -lQtCore -lpthread

# Compilation of cpp objects
CXX_OBJS:=$(patsubst %.cpp,$(GENDIR)/%.o,$(CXX_SRCS))
$(CXX_OBJS): $$(patsubst $(GENDIR)/%.o,%.cpp,$$@)
	@if test ! -e $(dir $@); then mkdir -p $(dir $@); fi
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -c -o $@

# .cpp dependency generation
CXX_DEPS:=$(patsubst %.cpp,$(GENDIR)/%.d,$(CXX_SRCS))
$(CXX_DEPS): $$(patsubst $(GENDIR)/%.d,%.cpp,$$@)
	@if test ! -e $(dir $@); then mkdir -p $(dir $@); fi
	$(CXX) $(INCLUDES) -MM -MT $(<:%.cpp=$(GENDIR)/%.o) -MF $@ $<
deps: $(CXX_DEPS)
include $(CXX_DEPS)

# QT MOC generation
QT_MOC_SRCS:=$(patsubst %.h,$(GENDIR)/%.moc.cpp,$(QT_HEADS))
$(QT_MOC_SRCS): $$(patsubst $(GENDIR)/%.moc.cpp,%.h,$$@)
	@if test ! -e $(dir $@); then mkdir -p $(dir $@); fi
	$(MOC) $< -o $@

QT_MOC_OBJS:=$(patsubst %.cpp,%.o,$(QT_MOC_SRCS))
$(QT_MOC_OBJS): $$(patsubst %.o,%.cpp,$$@)
	@if test ! -e $(dir $@); then mkdir -p $(dir $@); fi
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -c -o $@

# Deps for moc-generated cpps
QT_MOC_DEPS:=$(patsubst $(GENDIR)/%.cpp,$(GENDIR)/%.d,$(QT_MOC_SRCS))
$(QT_MOC_DEPS): $$(patsubst $(GENDIR)/%.d,$(GENDIR)/%.cpp,$$@)
	@if test ! -e $(dir $@); then mkdir -p $(dir $@); fi
	$(CXX) $(INCLUDES) -DQ_MOC_OUTPUT_REVISION=62 -MM -MT $(<:.cpp=.o) -MF $@ $<
mocdeps: $(QT_MOC_DEPS)
include $(QT_MOC_DEPS)

# Binary link rules
$(BINS): $$($$@_OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) $^ -o $@

tags: $(CXX_SRCS)
	ctags $(CXX_SRCS)

all: $(BINS) tags

clean:
	rm -rf $(GENDIR)
	rm -f $(BINS)
	rm -f tags

debugp:
	@echo "CXX_SRCS: $(CXX_SRCS)"
	@echo "CXX_OBJS: $(CXX_OBJS)"
	@echo "QT_HEADS: $(QT_HEADS)"
	@echo "QT_MOC_SRCS: $(QT_MOC_SRCS)"
	@echo "QT_MOC_OBJS: $(QT_MOC_OBJS)"

