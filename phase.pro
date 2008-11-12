include( common.pri )

HEADERS  = include/rootfinding.hpp
SOURCES  = phase.cpp
LIBS     = 
BOOST    = -lboost_program_options

include( system.pri )

CONFIG(debug, debug|release) {
	TARGET = phase_debug
	QMAKE_CXXFLAGS_DEBUG = -O0 -g
} else {
	TARGET  = phase
	DEFINES = NDEBUG
	QMAKE_CXXFLAGS_RELEASE = -O2
}
