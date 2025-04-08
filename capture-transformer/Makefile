CC=g++
PKGCONFIG = `pkg-config --cflags --libs opencv4`

CFLAGS= -O0 -g
LIBS= -lrt



HFILES= 
CFILES= 
CPPFILES= hough_circle.cpp hough_line.cpp canny.cpp sobel.cpp capture.cpp

SRCS= ${HFILES} ${CFILES}
CPPOBJS= ${CPPFILES:.cpp=.o}

all:	capture sobel canny hough_circle hough_line

clean:
	-rm -f *.o *.d cvtest*.ppm cvtest*.pgm test*.ppm test*.pgm
	-rm -f capture
	-rm -f sobel
	-rm -f canny
	-rm -f hough_line
	-rm -f hough_circle

distclean:
	-rm -f *.o *.d

hough_circle: hough_circle.o
	$(CC) $(CFLAGS) -o $@ $@.o $(PKGCONFIG)
hough_line: hough_line.o
	$(CC) $(CFLAGS) -o $@ $@.o $(PKGCONFIG)
canny: canny.o
	$(CC) $(CFLAGS) -o $@ $@.o $(PKGCONFIG)

sobel: sobel.o
	$(CC) $(CFLAGS) -o $@ $@.o $(PKGCONFIG)

capture: capture.o
	$(CC) $(CFLAGS) -o $@ $@.o $(PKGCONFIG)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<

.cpp.o:
	$(CC) $(CFLAGS) `pkg-config --cflags opencv4` -c $<
