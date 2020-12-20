COMPILER=$(CC)
ARCHIVER=$(AR)
CP=cp
$(info compiler=$(COMPILER))
$(info AR=$(ARCHIVER))
EXTRA_COMPILER_FLAGS=-Wall -Wextra
LIB=libxiic.a

RELEASEDIR=../lib
INCLUDEDIR=../include
INCLUDES=-I./. -I${INCLUDEDIR}

INCLUDEFILES=$(wildcard *.h)
LIBSOURCES=$(wildcard *.c)
OUTS = *.o
OBJECTS = $(addsuffix .o, $(basename $(wildcard *.c)))

libs:
	echo "******************* Compiling X-iic ****************"
	$(COMPILER) -c $(EXTRA_COMPILER_FLAGS) $(EXTRA_COMPILER_FLAGS) $(INCLUDES) $(LIBSOURCES) -D__linux__
	$(AR) rcs ${RELEASEDIR}/${LIB} $(OBJECTS)

include:
	${CP} $(INCLUDEFILES) $(INCLUDEDIR)

clean:
	rm -rf ${OBJECTS} 
