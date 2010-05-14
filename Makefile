CXX= g++
CXXFLAGS= -Wall -g3 -O0
INCLUDES=
LIBS= -lm -liputil
.SECONDEXPANSION:

BINARIES= rayTest

all: $(BINARIES) 

COMMON_OBJS = \
    colour.o \
    geom.o \
    image.o \
    ray.o \
    rayObject.o \
    sphere.o 

RAYTEST_OBJS= \
    $(COMMON_OBJS) \
    rayTest.o 
   
# Rules for compiling .cpp files
CXX_SRCS=$(wildcard *.cpp)
CXX_OBJS=$(CXX_SRCS:.cpp=.o)
$(CXX_OBJS): $$(patsubst %.o,%.cpp,$$(@)) $$(patsubst %.o,%.d,$$(@))
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(@:.o=.cpp) -c -o $(@) 

# Set up .cpp dependency generation
CXX_DEPENDS=$(CXX_SRCS:.cpp=.d)
$(CXX_DEPENDS): $$(patsubst %.d,%.cpp,$$@)
	$(CXX) -MM $(@:.d=.cpp) -o $(@)
-include $(CXX_DEPENDS)

# Build test binary
rayTest: $(RAYTEST_OBJS)
	$(CXX) $(CXXFLAGS) $(RAYTEST_OBJS) $(LIBS) -o rayTest

.phony = clean
clean: ; rm -f *.o *.d $(BINARIES)

.phony = debug_vars
debug_vars: 
	@echo 'CXX_DEPENDS: $(CXX_DEPENDS)'
	@echo 'CXX_SRCS: $(CXX_SRCS)'
