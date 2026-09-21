#include <Event/WindowEvent.hpp>
#include <PumpkinEngineCore.hpp>

class SandboxApplication : public Pumpkin::Core::Application {};

void dispatchMoveEvent(const Pumpkin::Core::WindowMoveEvent &e) {
  PE_LOG_INFO("{}", e.ToString());
}

void dispatchCloseEvent(const Pumpkin::Core::WindowCloseEvent &e) {
  PE_LOG_INFO("CLOSE IT!!!");
}

Pumpkin::Core::Application *CreatePumpkinApplication() {
  // Pumpkin::Core::WindowMoveEvent ev(1280, 720);
  Pumpkin::Core::WindowCloseEvent ev;

  Pumpkin::Core::EventDispatcher dispatcher(ev);

  dispatcher.Dispatch<Pumpkin::Core::WindowMoveEvent>(dispatchMoveEvent);
  dispatcher.Dispatch<Pumpkin::Core::WindowCloseEvent>(dispatchCloseEvent);

  return new SandboxApplication();
}
