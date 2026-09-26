#pragma once

#include "Renderer.hpp"
#include "WindowInfo.hpp"
#include <Core/Application.hpp>
#include <Core/Subsystem.hpp>
#include <Core/Time.hpp>
#include <SDL3/SDL.h>

namespace Pumpkin::SDL::Graphics {
class PESDLGraphiscSubsystem : public Core::PESubsystem {
public:
  PESDLGraphiscSubsystem(const WindowInfo &wndInfo) : m_WndInfo(wndInfo) {}

  void OnBegin() override;
  void OnShutdown() override;
  void OnUpdate(const Core::Time &time) override;
  void OnRender() override;

private:
  Core::Application *m_App = nullptr;
  SDL_Window *m_Window = nullptr;
  Renderer m_Renderer;
  WindowInfo m_WndInfo;
};
} // namespace Pumpkin::SDL::Graphics
