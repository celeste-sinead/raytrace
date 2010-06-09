CXX= g++
CXXFLAGS= -Wall -g3 -O0
INCLUDES=
LIBS= -lm -liputil
.SECONDEXPANSION:

BINARIES= rayTest
DEPSDIR= deps

all: $(BINARIES) depends

COMMON_OBJS = \
    colour.o \
    geom.o \
    image.o \
    ray.o \
    rayObject.o \
    sphere.o \
    view.o \
    world.o

RAYTEST_OBJS= \
    $(COMMON_OBJS) \
    rayTest.o 
   
# Rules for compiling .cpp files
CXX_SRCS=$(wildcard *.cpp)
CXX_OBJS=$(CXX_SRCS:.cpp=.o)
$(CXX_OBJS): $$(patsubst %.o,%.cpp,$$(@)) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(@:.o=.cpp) -c -o $(@) 

# Set up .cpp dependency generation
CXX_DEPENDS=$(patsubst %.cpp,$(DEPSDIR)/%.d,$(CXX_SRCS))
$(CXX_DEPENDS): $$(patsubst $(DEPSDIR)/%.d,%.cpp,$$@)
	$(CXX) -MM $(patsubst $(DEPSDIR)/%.d,%.cpp,$@) -o $(@)
.phony = depends
depends: $(CXX_DEPENDS)
-include $(CXX_DEPENDS)

# Build test binary
rayTest: $(RAYTEST_OBJS)
	$(CXX) $(CXXFLAGS) $(RAYTEST_OBJS) $(LIBS) -o rayTest

.phony = test
test: rayTest
	./rayTest

.phony = clean
clean: ; rm -f *.o $(DEPSDIR)/*.d $(BINARIES)

.phony = debug_vars
debug_vars: 
	@echo 'CXX_DEPENDS: $(CXX_DEPENDS)'
	@echo 'CXX_SRCS: $(CXX_SRCS)'
