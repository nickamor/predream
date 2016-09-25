CXXFLAGS := $(CXXFLAGS)-std=c++11 $(shell sdl2-config --cflags)
LDFLAGS  := $(LDFLAGS) $(shell sdl2-config --libs) -lSDL2_ttf

.PHONY: all clean

all: game

game: main.o
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $^ -c -o $@

clean:
	$(RM) game *.o
