#include <PumpkinEngineCore.hpp>

class SandboxApplication : public Pumpkin::Application {};

Pumpkin::Application *CreatePumpkinApplication() {
  PE_LOG_TRACE("Hello, World!");
  PE_LOG_INFO("Hello, {}!", "World");
  PE_LOG_WARN("Hello, {1}{0}", '!', "World");
  PE_LOG_ERROR("Hello, World!");

  PE_LOG_CORE_TRACE("Hello, World!");
  PE_LOG_CORE_INFO("Hello, World!");
  PE_LOG_CORE_WARN("Hello, World!");
  PE_LOG_CORE_ERROR("Hello, World!");

  return new SandboxApplication();
}
