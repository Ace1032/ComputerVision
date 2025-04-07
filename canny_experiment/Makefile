INCLUDE_DIRS = `pkg-config --cflags opencv4`
LIB_DIRS = 
CC = g++

CDEFS =
CFLAGS = -O0 -pg -g $(INCLUDE_DIRS) $(CDEFS)
LIBS = `pkg-config --libs opencv4`

HFILES =
CFILES =
CPPFILES = capture.cpp

SRCS = ${HFILES} ${CFILES}
CPPOBJS = ${CPPFILES:.cpp=.o}

all: capture

clean:
	-rm -f *.o *.d
	-rm -f capture

distclean:
	-rm -f *.o *.d

capture: capture.o
	$(CC) $(CFLAGS) -o $@ capture.o $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

.cpp.o:
	$(CC) $(CFLAGS) -c $<

