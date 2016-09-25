#include <exception>
#include <iostream>
#include "application.h"

int main() {
  try {
    Application app;
    app.Clear();
    app.ShowWindow();
    app.RenderText("Loading...", 0, 0, true);
    app.Present();
    
    app.Delay(2000);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
