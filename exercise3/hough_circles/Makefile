CC = g++

# Use pkg-config to fetch OpenCV 4 flags
OPENCV_CFLAGS = `pkg-config --cflags opencv4`
OPENCV_LIBS   = `pkg-config --libs opencv4`

# Debug & optimization flags
CFLAGS = -O0 -g $(OPENCV_CFLAGS)

# Source files
CPPFILES = capture.cpp
CPPOBJS  = $(CPPFILES:.cpp=.o)

# Build target
all: capture

capture: $(CPPOBJS)
	$(CC) -o $@ $^ $(OPENCV_LIBS)

# Compilation rule
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f *.o capture

distclean: clean
