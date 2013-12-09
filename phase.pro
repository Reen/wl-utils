include( common.pri )

HEADERS  = include/rootfinding.hpp misc.h
SOURCES  = phase.cpp misc.cpp
LIBS     = 
BOOST    = -lboost_program_options -lboost_regex -lboost_thread-mt -lboost_iostreams -lboost_filesystem -lboost_system

include( system.pri )

CONFIG(debug, debug|release) {
	TARGET = phase_debug
	QMAKE_CXXFLAGS_DEBUG = -O0 -g
} else {
	TARGET  = phase
	DEFINES = NDEBUG
	QMAKE_CXXFLAGS_RELEASE = -O2
}
