#pragma once

#include "Core/Time.hpp"

namespace Pumpkin::Core {
class Application {
public:
  Application();
  virtual ~Application();

  virtual void OnCreated() {}
  void Run();
  void Shutdown();

  inline static Application *&GetApp() { return s_App; }

private:
  static Application *s_App;
  bool m_IsRunning;
  Time m_Time;
};
} // namespace Pumpkin::Core
