#include <PumpkinEngineCore.hpp>
#include <PumpkinEngineSDLGraphics.hpp>

class SandboxApplication : public Pumpkin::Core::Application {
  void OnCreated() override {
    GetSubsystemManager()
        .RegisterSubsystem<Pumpkin::SDL::Graphics::PESDLGraphiscSubsystem>(
            Pumpkin::SDL::Graphics::WindowInfo{
                .Width = 800, .Height = 600, .Title = "Hello, World!"});
  }
};

Pumpkin::Core::Application *CreatePumpkinApplication() {
  PE_LOG_TRACE("Position: {}", Pumpkin::Core::PEVec2(1, 1));
  PE_LOG_ERROR("E is {}", Pumpkin::Core::PEMat4(1.f));
  return new SandboxApplication();
}
