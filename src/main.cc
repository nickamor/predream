#include <exception>
#include <iostream>
#include "application.h"

int main() {
  try {
    Application app;
    app.ShowWindow();
    app.Clear();
    app.RenderText("Loading...", 0, 0, true);
    app.Present();
    
    SDL_Event event;
    bool done = false;
    while (!done) {
      while (SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT:
          case SDL_KEYDOWN:
          done = true;
          break;
        }
      }

      app.Clear();
      app.Present();
    }
  } catch (std::exception &e) {
    std::cerr << "Fatal error: " << e.what() << std::endl;
    return 1;
  }
}

