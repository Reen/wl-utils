# bei Problemen mit nicht gefunden shared libraries folgendes bearchten!:
# http://www.eyrie.org/~eagle/notes/rpath.html
# export LD_RUN_PATH=/cluster/rhab/usr/lib
# oder korrekten rpath über linker flags dauerhaft setzen
macx-g++ {
	INCLUDEPATH += /Users/rhab/usr/include
	INCLUDEPATH += /sw/include
	LIBS        += -L/Users/rhab/usr/lib -L/sw/lib
	#BOOST       ~= s/-l([a-z_]+)/-l\\1-xgcc40-mt/g
}

linux-g++-64 {
	INCLUDEPATH += /cluster/rhab/usr/include
	LIBS        += -L/cluster/rhab/usr/lib
	QMAKE_LFLAGS += '-Wl,-rpath,/cluster/rhab/usr/lib'
	#BOOST       ~= s/-l([a-z_]+)/-l\1-gcc41-mt/g
}

LIBS += $$BOOST
