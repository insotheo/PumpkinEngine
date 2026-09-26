#include "Core/Application.hpp"
#include <chrono>

namespace Pumpkin::Core {
Application *Application::s_App = nullptr;

Application::Application() : m_IsRunning(false) { s_App = this; }

Application::~Application() { Shutdown(); }

void Application::Run() {
  m_IsRunning = true;

  OnCreated();

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

    m_SubsystemManager.UpdateAll(m_Time);

    if (!m_IsRunning)
      break;

    m_SubsystemManager.RenderAll();
  }
}

void Application::PostEvent(Event &event) {
  m_SubsystemManager.OnEventAll(event);
}

void Application::Shutdown() {
  if (!m_IsRunning)
    return;

  m_IsRunning = false;

  m_SubsystemManager.ShutdownAll();
}
} // namespace Pumpkin::Core
