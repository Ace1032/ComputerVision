CXX = g++
CXXFLAGS = -Wall -O2 `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`

TARGET = my_stream
SRC =my_stream.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	rm -f $(TARGET)
