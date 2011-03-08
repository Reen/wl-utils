# bei Problemen mit nicht gefunden shared libraries folgendes bearchten!:
# http://www.eyrie.org/~eagle/notes/rpath.html
# export LD_RUN_PATH=/cluster/rhab/usr/lib
macx-g++ {
	INCLUDEPATH += /Users/rene/usr/include
	LIBS        += -L/Users/rene/usr/lib
	BOOST       ~= s/-l([a-z_]+)/-l\1-xgcc40-mt/g
}

linux-g++-64 {
	INCLUDEPATH += /cluster/rhab/usr/include
	LIBS        += -L/cluster/rhab/usr/lib
	#BOOST       ~= s/-l([a-z_]+)/-l\1-gcc41-mt/g
}

LIBS += $$BOOST
