CXXFLAGS+=-std=c++11
CXXFLAGS+=-O3

CXX=clang++

LDLIBS+=-lstdc++fs
LDLIBS+=-lboost_system
LDLIBS+=-lboost_program_options
LDLIBS+=-lpthread

.PHONY: default-target
default-target: loc

.PHONY: clean
clean:
	$(RM) loc
