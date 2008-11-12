TEMPLATE = app
CONFIG   = release incremental global_init_link_order lib_version_first plugin_no_soname link_prl build_all warn_off

HEADERS  = 
SOURCES  = filter.cpp
INCLUDEPATH = ./include
LIBS     = 
BOOST    = -lboost_thread -lboost_iostreams -lboost_filesystem -lboost_system

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
	TARGET = filter_debug
	QMAKE_CXXFLAGS_DEBUG = -O0 -g
} else {
	TARGET  = filter
	DEFINES = NDEBUG
	QMAKE_CXXFLAGS_RELEASE = -O3 -msse -msse2 -ftree-vectorize
}
