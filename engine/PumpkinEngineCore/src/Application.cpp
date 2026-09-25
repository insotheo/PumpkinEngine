#include "Core/Application.hpp"
#include <chrono>

namespace Pumpkin::Core {
Application *Application::s_App;

Application::Application() : m_IsRunning(false) { s_App = this; }

Application::~Application() { Shutdown(); }

void Application::Run() {
  m_IsRunning = true;

  auto lastTime = std::chrono::high_resolution_clock::now();

  while (m_IsRunning) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(currentTime - lastTime).count();
    lastTime = currentTime;

    if (dt > 0.1f)
      dt = 0.1f;

    m_Time.DeltaTime = dt;
    m_Time.TotalTime += dt;
    m_Time.FrameCount++;
  }
}

void Application::Shutdown() { m_IsRunning = false; }
} // namespace Pumpkin::Core
