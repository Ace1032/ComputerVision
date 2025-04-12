OPENCV_CFLAGS = `pkg-config --cflags opencv4`
OPENCV_LIBS   = `pkg-config --libs opencv4`

CC = g++
CFLAGS = -O0 -g $(OPENCV_CFLAGS)
LDFLAGS = 
LIBS = $(OPENCV_LIBS)

CPPFILES = capture.cpp
CPPOBJS = ${CPPFILES:.cpp=.o}

all: capture

capture: $(CPPOBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o capture
