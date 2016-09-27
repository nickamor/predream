CXXFLAGS := $(CXXFLAGS)-std=c++14 $(shell sdl2-config --cflags) -Iinclude/
LDFLAGS  := $(LDFLAGS) $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net

.PHONY: all clean

all: game

game: main.o application.o
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: src/%.cc
	$(CXX) $(CXXFLAGS) $^ -c -o $@

clean:
	$(RM) game *.o
