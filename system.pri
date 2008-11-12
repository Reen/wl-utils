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