#include <PumpkinEngineCore.hpp>

class SandboxApplication : public Pumpkin::Application {};

Pumpkin::Application *CreatePumpkinApplication() {
  return new SandboxApplication();
}
