#include <PumpkinEngineCore.hpp>

class SomeUselessSubsystem : public Pumpkin::Core::PESubsystem {
public:
  void OnBegin() override { PE_LOG_WARN("Subsystem was initialized!"); }
  void OnShutdown() override { PE_LOG_WARN("Subsystem was shutted down!"); }

  void OnUpdate(const Pumpkin::Core::Time &time) override {
    PE_LOG_INFO("FPS: {}", 1 / time.DeltaTime);
  }
};

class SandboxApplication : public Pumpkin::Core::Application {
  void OnCreated() override {
    GetSubsystemManager().RegisterSubsystem<SomeUselessSubsystem>();
  }
};

Pumpkin::Core::Application *CreatePumpkinApplication() {
  return new SandboxApplication();
}
