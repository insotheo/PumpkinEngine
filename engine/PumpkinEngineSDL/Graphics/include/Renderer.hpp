#pragma once

#include <SDL3/SDL.h>

namespace Pumpkin::SDL::Graphics {
class Renderer {
public:
  Renderer() {}
  ~Renderer() { Shutdown(); }

  inline bool IsCreatedSuccessfully() const { return m_Device; }

  void Init(SDL_Window *wnd);
  void Shutdown();

  void Render();

private:
  SDL_GPUDevice *m_Device = nullptr;
  SDL_Window *m_Wnd = nullptr;
};
} // namespace Pumpkin::SDL::Graphics
