
ALL: power
CFLAGS = -O3
FFLAGS = 
CPPFLAGS = -O3
FPPFLAGS = 
CLEANFILES = power 

include ${PETSC_DIR}/conf/base

power: power.o chkopts 
	${CLINKER} -o power power.o ${PETSC_LIB} -lz
	${RM} power.o
