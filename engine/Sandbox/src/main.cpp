#include <PumpkinEngine.h>

class SandboxApp : public Pumpkin::Application{
    public:
        SandboxApp(){
            //custom ctor

            PE_LOG_TRACE("Hello, {}!", "World");
            PE_LOG_INFO("Hello, World!");
            PE_LOG_WARN("Hello, World!");
            PE_LOG_ERROR("Hello, World!");
        }
};

Pumpkin::Application* Pumpkin::CreateApplication(){
    return new SandboxApp();
}