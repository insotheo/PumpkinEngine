#pragma once

namespace Pumpkin::Core {
class Application {
public:
  static Application *s_App;

  Application();
  virtual ~Application();

  void Run();
  void Shutdown();

private:
  bool m_IsRunning;
};
} // namespace Pumpkin::Core
