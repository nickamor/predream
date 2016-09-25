#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <stdexcept>
#include "SDL.h"
#include "SDL_ttf.h"

class SdlRuntimeError : public std::runtime_error {
public:
  SdlRuntimeError() : std::runtime_error(SDL_GetError()) {};
};

class Application {
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  static const unsigned int window_flags = SDL_WINDOW_HIDDEN;
  static const int width = 800;
  static const int height = 600;
public:
  Application() throw(SdlRuntimeError);
  ~Application();
  
  void ShowWindow();
  void Delay(unsigned int delay);
  void Clear() throw(SdlRuntimeError);
  void Present();
  void RenderText(const std::string& message, int x, int y, bool inverse_origin = false) throw(SdlRuntimeError);
};

#endif
