include( common.pri )

HEADERS  = 
SOURCES  = filter.cpp
LIBS     = 
BOOST    = -lboost_thread-mt -lboost_iostreams -lboost_filesystem -lboost_system

include( system.pri )

CONFIG(debug, debug|release) {
	TARGET = filter_debug
	QMAKE_CXXFLAGS_DEBUG = -O0 -g
} else {
	TARGET  = filter
	DEFINES = NDEBUG
	QMAKE_CXXFLAGS_RELEASE = -O3 -msse -msse2 -ftree-vectorize
}
