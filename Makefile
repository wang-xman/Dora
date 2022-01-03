# Makefile
# Create a shared library libdora.so

CXX := g++
# For both GNU g++ and clang++
# With clang++ flag c++11 is a must.
CXXFLAGS := -g -Wall -std=c++11
# Directories
DORAPATH := ${DORA_PROJECT_ROOT}/
INCDIR := ${DORA_PROJECT_ROOT}/include/
SRCDIR := ${DORA_PROJECT_ROOT}/src/
BLDDIR := ${DORA_PROJECT_ROOT}/build/

# List source and object files
SOURCES := $(wildcard ${SRCDIR}*.cpp)
OBJECTS := $(patsubst ${SRCDIR}%.cpp, ${BLDDIR}%.o, ${SOURCES})

# Shared library path/name
SHRDLIB := ${BLDDIR}libdora.so

# Ultimate target is shared lib
all: ${SHRDLIB}

# Shared lib: Link all object files into a shared library.
${SHRDLIB}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -shared -o $@

# Object files : Compile source files into object files.
${OBJECTS}: ${BLDDIR}%.o: ${SRCDIR}%.cpp
	${CXX} ${CXXFLAGS} -c $< -fPIC -o $@ -I${INCDIR}

clean_objects:
	rm -rf $(OBJECTS)

.PHONEY: all clean_objects