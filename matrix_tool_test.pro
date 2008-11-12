include( common.pri )

HEADERS  = q_matrix.h state.h
SOURCES  = matrix_tool_test.cpp
LIBS     = -lz -fopenmp
BOOST    = -lboost_thread -lboost_serialization -lboost_iostreams -lboost_test_exec_monitor

include( system.pri )

CONFIG(debug, debug|release) {
	TARGET = matrix_tool_test_debug
	QMAKE_CXXFLAGS_DEBUG = -O0 -g
} else {
	TARGET  = matrix_tool_test
	QMAKE_CXXFLAGS_RELEASE = -O3 -msse -msse2 -fomit-frame-pointer -ftree-vectorize -fopenmp
}
