PROG := rational
SHELL := /bin/sh
CC := gcc
CXX := clang++

COMPILER_OPTIONS := -m64 -Wall -Wextra -Wshadow -Werror -pedantic -Iinclude
CFLAGS := -std=c99 $(COMPILER_OPTIONS)
CXXFLAGS := -std=c++11 -stdlib=libc++ -Weffc++ $(COMPILER_OPTIONS)
#CXXFLAGS := -std=c++11 -stdlib=libc++ -w $(COMPILER_OPTIONS)
#CXXFLAGS := -Weffc++ $(COMPILER_OPTIONS)
LDFLAGS := -lm

DEBUGFLAGS := -g -O0 -D _DEBUG
RELEASEFLAGS := -O2 -D NDEBUG

TARGET  := rational-test.x
SOURCES := $(shell echo src/*.cpp)
HEADERS := $(shell echo include/*.h)
COMMON  :=
OBJECTS := $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(COMMON)
	$(CXX) $(FLAGS) $(CXXFLAGS) $(DEBUGFLAGS) -o $(TARGET) $(OBJECTS)

release: $(SOURCES) $(HEADERS) $(COMMON)
	$(CXX) $(FLAGS) $(CXXFLAGS) $(RELEASEFLAGS) -o $(TARGET) $(SOURCES)

zip:
	-zip $(PROG).zip $(HEADERS) $(SOURCES) Makefile GRADER_INFO.txt

clean:
	-rm -f $(TARGET) $(OBJECTS) $(PROG).zip

%.o: %.cpp $(HEADERS) $(COMMON)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c -o $@ $<

.PHONY : all release
