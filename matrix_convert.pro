include( common.pri )

HEADERS  = matrix_generics.h
HEADERS += q_matrix.h
HEADERS += state.h
SOURCES  = matrix_convert.cpp
LIBS     = -lz
BOOST    = -lboost_thread -lboost_serialization -lboost_iostreams -lboost_filesystem -lboost_system

include( system.pri )

CONFIG(debug, debug|release) {
	TARGET = matrix_convert_debug
	QMAKE_CXXFLAGS_DEBUG = -O0 -g
} else {
	TARGET  = matrix_convert
	DEFINES = NDEBUG
	QMAKE_CXXFLAGS_RELEASE = -O3 -msse -msse2 -fomit-frame-pointer -ftree-vectorize
}
