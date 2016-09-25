#include "application.h"

template <typename... Args>
void SafeSDLCall(int func(Args...), Args... args) throw(SdlRuntimeError) {
  int retval = func(args...);

  if (retval != 0) {
    throw SdlRuntimeError();
  }
}

Application::Application() throw(SdlRuntimeError) {
  SafeSDLCall(SDL_CreateWindowAndRenderer, width, height, window_flags, &window, &renderer);
  SafeSDLCall(TTF_Init);
  font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf", 14);
  
  if (font == 0) {
    throw SdlRuntimeError();
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

void Application::Clear() throw(SdlRuntimeError) {
  SafeSDLCall(SDL_RenderClear, renderer);
}

void Application::Present() {
  SDL_RenderPresent(renderer);
}

void Application::RenderText(const std::string& message, int x, int y, bool inverse_origin) throw(SdlRuntimeError) {
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
