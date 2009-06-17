include( common.pri )

HEADERS  = include/rootfinding.hpp
SOURCES  = error.cpp
LIBS     = -lmpfr
BOOST    = -lboost_iostreams

include( system.pri )

CONFIG(debug, debug|release) {
	TARGET = error_debug
	QMAKE_CXXFLAGS_DEBUG = -O0 -g
} else {
	TARGET  = error
	DEFINES = NDEBUG
	QMAKE_CXXFLAGS_RELEASE = -O2
}
