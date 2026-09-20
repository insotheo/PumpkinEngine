#include <Application.hpp>

namespace Pumpkin {
Application *Application::s_App;

Application::Application() : m_IsRunning(false) { s_App = this; }

Application::~Application() { Shutdown(); }

void Application::Run() {
  m_IsRunning = true;

  while (m_IsRunning)
    ;
}

void Application::Shutdown() { m_IsRunning = false; }
} // namespace Pumpkin
