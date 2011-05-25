include( common.pri )

HEADERS  = q_matrix.h state.h misc.h normalize.h eigenvector.h combine.h variance.h
SOURCES  = matrix_tool.cpp misc.cpp normalize.cpp eigenvector.cpp combine.cpp variance.cpp
LIBS     = -lz
BOOST    = -lboost_regex -lboost_thread -lboost_iostreams -lboost_filesystem -lboost_system

include( system.pri )

CONFIG(debug, debug|release) {
	TARGET = matrix_tool_debug
	QMAKE_CXXFLAGS_DEBUG = -O0 -g
} else {
	TARGET  = matrix_tool
	DEFINES = NDEBUG
	QMAKE_CXXFLAGS_RELEASE = -O3 -msse -msse2 -msse3 -msse4 -fomit-frame-pointer -ftree-vectorize
}
