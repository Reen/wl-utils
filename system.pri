macx-g++ {
	INCLUDEPATH += /Users/rene/usr/include
	INCLUDEPATH += /sw/include
	LIBS        += -L/Users/rene/usr/lib -L/sw/lib
	BOOST       ~= s/-l([a-z_]+)/-l\1-xgcc40-mt/g
}

linux-g++-64 {
	INCLUDEPATH += /cluster2/rhab/usr/include/boost-1_38
	INCLUDEPATH += /cluster2/rhab/usr/include
	LIBS        += -L/cluster2/rhab/usr/lib
	BOOST       ~= s/-l([a-z_]+)/-l\1-gcc41-mt/g
}

LIBS += $$BOOST
