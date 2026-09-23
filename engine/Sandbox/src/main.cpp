#include <PumpkinEngineCore.hpp>

class SandboxApplication : public Pumpkin::Core::Application {
  void OnCreated() override {
    PE_LOG_INFO("This is preload");
    PE_LOG_WARN("-----");
  }
};

Pumpkin::Core::Application *CreatePumpkinApplication() {
  return new SandboxApplication();
}
