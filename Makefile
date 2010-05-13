CXX= g++
CXXFLAGS= -Wall -g3 -O0
INCLUDES=
LIBS= -lm
.SECONDEXPANSION:

all: rayTest

BINARIES= rayTest

COMMON_OBJS = \
    colour.o \
    geom.o \
    ray.o \
    rayObject.o \
    sphere.o 

RAYTEST_OBJS= \
    $(COMMON_OBJS) \
    rayTest.o 
    
CXX_SRCS=$(wildcard *.cpp)
CXX_OBJS=$(CXX_SRCS:.cpp=.o)
$(CXX_OBJS): $$(patsubst %.o,%.cpp,$$(@))
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(@:.o=.cpp) -c -o $(@) 

rayTest: $(RAYTEST_OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(RAYTEST_OBJS) -o rayTest

.phony = clean

clean: ; rm $(CXX_OBJS) $(BINARIES)
