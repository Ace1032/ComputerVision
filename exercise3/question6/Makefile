CXX = g++
CXXFLAGS = -O2 `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`

all: topdown_tracker video_to_pgm bottom_up_tracker

topdown_tracker: topdown_tracker.cpp
	$(CXX) $(CXXFLAGS) -o topdown_tracker topdown_tracker.cpp $(LDFLAGS)

video_to_pgm: vido_to_pgm.cpp
	$(CXX) $(CXXFLAGS) -o video_to_pgm vido_to_pgm.cpp $(LDFLAGS)

bottom_up_tracker: compute_com.cpp
	$(CXX) $(CXXFLAGS) -o bottom_up_tracker compute_com.cpp $(LDFLAGS)

clean:
	rm -f topdown_tracker video_to_pgm bottom_up_tracker  *.o

