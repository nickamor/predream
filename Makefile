CXXFLAGS := $(CXXFLAGS)-std=c++11 $(shell sdl2-config --cflags) -Iinclude/
LDFLAGS  := $(LDFLAGS) $(shell sdl2-config --libs) -lSDL2_ttf

.PHONY: all clean

all: game

game: main.o application.o
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: src/%.cc
	$(CXX) $(CXXFLAGS) $^ -c -o $@

clean:
	$(RM) game *.o
