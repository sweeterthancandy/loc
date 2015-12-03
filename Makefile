CXXFLAGS+=-std=c++11
CXXFLAGS+=-ggdb3

CXX=clang++

LDLIBS+=-lboost_filesystem
LDLIBS+=-lboost_system
LDLIBS+=-lboost_program_options
LDLIBS+=-lpthread

.PHONY: default-target
default-target: loc

.PHONY: clean
clean:
	$(RM) loc
