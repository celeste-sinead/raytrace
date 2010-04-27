CXX= g++
CXXFLAGS= -Wall -g3 -O0
INCLUDES=
LIBS= -lm
.SECONDEXPANSION:

all: rayTest

BINARIES= rayTest

RAYTEST_OBJS= \
    colour.o \
    geom.o \
    ray.o \
    rayObject.o \
    sphere.o 

CXX_SRCS=$(wildcard *.cpp)
CXX_OBJS=$(CXX_SRCS:.cpp=.o)
$(CXX_OBJS): $$(patsubst %.o,%.cpp,$$(@))
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(@:.o=.cpp) -c -o $(@) 

rayTest: $(RAYTEST_OBJS)

.phony = clean

clean: ; rm $(CXX_OBJS) $(BINARIES)
