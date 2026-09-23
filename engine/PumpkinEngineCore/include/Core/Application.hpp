#pragma once

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
};
} // namespace Pumpkin::Core
