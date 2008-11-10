TEMPLATE = app
CONFIG   = release incremental global_init_link_order lib_version_first plugin_no_soname link_prl warn_off

HEADERS  = q_matrix.h state.h
SOURCES  = matrix_tool_test.cpp
INCLUDEPATH = ./include
LIBS     = -lz -fopenmp
BOOST    = -lboost_thread -lboost_serialization -lboost_iostreams -lboost_test_exec_monitor

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
#DEFINES = NDEBUG
QMAKE_CXXFLAGS_RELEASE = -O3 -fomit-frame-pointer -ftree-vectorize -fopenmp

