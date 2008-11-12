include( common.pri )

HEADERS  = q_matrix.h state.h
SOURCES  = matrix_tool.cpp
LIBS     = -lz
BOOST    = -lboost_thread -lboost_serialization -lboost_iostreams

include( system.pri )

CONFIG(debug, debug|release) {
	TARGET = matrix_tool_debug
	QMAKE_CXXFLAGS_DEBUG = -O0 -g
} else {
	TARGET  = matrix_tool
	DEFINES = NDEBUG
	QMAKE_CXXFLAGS_RELEASE = -O3 -msse -msse2 -fomit-frame-pointer -ftree-vectorize
}
