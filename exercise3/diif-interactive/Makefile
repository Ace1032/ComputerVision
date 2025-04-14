CC = g++
CFLAGS = -O0 -g `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`

# Source and target
TARGET = motion_diff
SRC = capture.cpp
OBJ = $(SRC:.cpp=.o)

# Default rule
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f *.o $(TARGET)
