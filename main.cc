#include <exception>
#include <stdexcept>
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"

class SdlRuntimeError : public std::runtime_error {
public:
  SdlRuntimeError();
};

SdlRuntimeError::SdlRuntimeError() : std::runtime_error(SDL_GetError()) {}

template <typename... Args>
void SafeSDLCall(int func(Args...), Args... args) throw(std::runtime_error) {
  int retval = func(args...);

  if (retval != 0) {
    throw std::runtime_error(SDL_GetError());
  }
}

class Application {
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  static const unsigned int window_flags = SDL_WINDOW_HIDDEN;
  static const int width = 800;
  static const int height = 600;
public:
  Application();
  ~Application();
  
  void ShowWindow();
  void Delay(unsigned int delay);
  void Clear() throw(std::runtime_error);
  void Present();
  void DrawText(const std::string& message, int x, int y, bool inverse_origin = false);
};

Application::Application() {
  SafeSDLCall(SDL_CreateWindowAndRenderer, width, height, window_flags, &window, &renderer);
  SafeSDLCall(TTF_Init);
  font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf", 14);
  
  if (font == 0) {
    throw std::runtime_error(TTF_GetError());
  }
}

Application::~Application() {
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Application::ShowWindow() {
  SDL_ShowWindow(window);
}

void Application::Delay(unsigned int delay) {
  SDL_Delay(delay);
}

void Application::Clear() throw(std::runtime_error) {
  SafeSDLCall(SDL_RenderClear, renderer);
}

void Application::Present() {
  SDL_RenderPresent(renderer);
}

void Application::DrawText(const std::string& message, int x, int y, bool inverse_origin) {
  int w, h;
  SafeSDLCall(TTF_SizeUTF8, font, message.c_str(), &w, &h);
  
  SDL_Color color = {255, 255, 255, 255};
  SDL_Surface *surface = TTF_RenderUTF8_Blended(font, message.c_str(), color);
  
  if (surface == 0) {
    throw SdlRuntimeError();
  }
  
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  
  if (texture == 0) {
    throw SdlRuntimeError();
  }
  
  SDL_Rect srcrect = {0, 0, w, h}, dstrect = {x, y, w, h};
  if (inverse_origin) {
    dstrect.x = (width - w) - x;
    dstrect.y = (height - h) - y;
  }
  
  SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
  
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

int main() {
  try {
    Application app;
    app.Clear();
    app.ShowWindow();
    app.DrawText("Loading...", 0, 0, true);
    app.Present();
    
    app.Delay(2000);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
