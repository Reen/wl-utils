TEMPLATE = app
CONFIG   = release incremental global_init_link_order lib_version_first plugin_no_soname link_prl build_all warn_off
#CONFIG -= qt app_bundle warn_on qt_framework uic resources sdk rez no_mocdepend
#COFNIG += release debug_and_release build_all

HEADERS  = q_matrix.h state.h
SOURCES  = matrix_tool.cpp
INCLUDEPATH = ./include
LIBS     = -lz -fopenmp
BOOST    = -lboost_thread -lboost_serialization -lboost_iostreams

macx {
	INCLUDEPATH += /Users/rene/usr/include
	LIBS        += -L/Users/rene/usr/lib
	BOOST       ~= s/-l([a-z_]+)/-l\1-xgcc43-mt/g
}

linux-g++-64 {
	INCLUDEPATH += /cluster2/rhab/usr/include/boost-1_38
	LIBS        += -L/cluster2/rhab/usr/lib
	BOOST       ~= s/-l([a-z_]+)/-l\1-gcc41-mt/g
}

LIBS += $$BOOST

CONFIG(debug, debug|release) {
	message($$CONFIG)
	message(debug)
	TARGET = matrix_tool_debug
	QMAKE_CXXFLAGS_DEBUG = -O0 -g
} else {
	message($$CONFIG)
	message(release)
	TARGET  = matrix_tool
	DEFINES = NDEBUG
	QMAKE_CXXFLAGS_RELEASE = -O3 -msse -msse2 -fomit-frame-pointer -ftree-vectorize -fopenmp
}
