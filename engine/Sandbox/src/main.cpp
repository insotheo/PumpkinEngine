#include <PumpkinEngineCore.hpp>

class SandboxApplication : public Pumpkin::Core::Application {};

Pumpkin::Core::Application *CreatePumpkinApplication() {
  return new SandboxApplication();
}
