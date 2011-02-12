CXX= g++
CXXFLAGS= -Wall -g3 -O0
MOC= moc-qt4
INCLUDES= -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4
LIBS= -lm -liputil -lQtGui -lQtCore -lpthread
.SECONDEXPANSION:

BINARIES= rayTest
DEPSDIR= deps
OBJDIR= obj
QTDIR= qt

all: $(BINARIES) 
	ctags -R .

COMMON_OBJS= \
    colour.o \
    geom.o \
    image.o \
    ray.o \
    rayObject.o \
    view.o \
    world.o 

RAYTEST_OBJS= \
    rayTest.o 

# Headers declaring Qt objects, which therefore need moc treatment
QT_HEADS = image.h

# Add objdir prefix to the above:
COMMON_OBJS:=$(patsubst %,$(OBJDIR)/%,$(COMMON_OBJS))
RAYTEST_OBJS:=$(patsubst %,$(OBJDIR)/%,$(RAYTEST_OBJS))
# Add special qt moc objects:
COMMON_OBJS:=$(COMMON_OBJS) $(patsubst %.h,$(QTDIR)/moc_%.o,$(QT_HEADS))

# Rules for compiling .cpp files
CXX_SRCS:=$(wildcard *.cpp)
CXX_OBJS:=$(patsubst %.cpp,$(OBJDIR)/%.o,$(CXX_SRCS))
$(CXX_OBJS): $$(patsubst obj/%.o,%.cpp,$$@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -c -o $@

# Set up .cpp dependency generation
CXX_DEPENDS=$(patsubst %.cpp,$(DEPSDIR)/%.d,$(CXX_SRCS))
$(CXX_DEPENDS): $$(patsubst $(DEPSDIR)/%.d,%.cpp,$$@) 
	$(CXX) -MM -MT $(<:%.cpp=$(OBJDIR)/%.o) -MF $@ $<
.phony = depends
depends: $(CXX_DEPENDS)
-include $(CXX_DEPENDS)

# QT MOC generation
QT_MOC_SRCS:=$(patsubst %.h,$(QTDIR)/moc_%.cpp,$(QT_HEADS))
$(QT_MOC_SRCS): $$(patsubst $(QTDIR)/moc_%.cpp,%.h,$$@)
	$(MOC) $< -o $@ 

QT_MOC_OBJS:=$(QT_MOC_SRCS:%.cpp=%.o)
$(QT_MOC_OBJS): $$(patsubst %.o,%.cpp,$$@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -c -o $@

# Deps for moc-generated cpps
QT_MOC_DEPS:=$(QT_MOC_SRCS:%.cpp=%.d)
$(QT_MOC_DEPS): $$(patsubst %.d,%.cpp,$$@)
	$(CXX) -DQ_MOC_OUTPUT_REVISION=62 -MM -MT $(<:.cpp=.o) -MF $@ $<
# NB: the -DQ_MOC... is a hack to get around the generated protections
# which want QObject included, which isn't done for MM (bleargh)
-include $(QT_MOC_DEPS)

# Build test binary
rayTest: $(COMMON_OBJS) $(RAYTEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

.phony = test
test: rayTest
	./rayTest

.phony = clean
clean: 
	rm -f $(OBJDIR)/*.o 
	rm -f $(DEPSDIR)/*.d 
	rm -f $(QTDIR)/*.o $(QTDIR)/*.cpp $(QTDIR)/*.d
	rm -f $(BINARIES)

.phony = debug_vars
debug_vars: 
	@echo 'CXX_DEPENDS: $(CXX_DEPENDS)'
	@echo 'CXX_SRCS: $(CXX_SRCS)'
