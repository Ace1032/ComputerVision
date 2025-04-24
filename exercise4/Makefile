CXX = g++
CXXFLAGS = `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`

SRC = laneDetection.cpp
SRC2 = skeletal_live.cpp

TARGET = lane_detector
TARGET2 = skeletal_live

all: $(TARGET) $(TARGET2)

$(TARGET): $(SRC)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)


$(TARGET2): $(SRC2)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(TARGET2)
