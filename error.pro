include( common.pri )

HEADERS  = include/rootfinding.hpp exact_dos.h wl_exceptions.h
SOURCES  = error.cpp
LIBS     = -lmpfr -lgmp
BOOST    = -lboost_iostreams -lboost_filesystem -lboost_system

include( system.pri )

CONFIG(debug, debug|release) {
	TARGET = error_debug
	QMAKE_CXXFLAGS_DEBUG = -O0 -g
} else {
	TARGET  = error
	DEFINES = NDEBUG
	QMAKE_CXXFLAGS_RELEASE = -O2
}
