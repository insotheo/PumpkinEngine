#include <PumpkinEngine.h>
#include <Core/Layer.h>

class SandboxLayer : public Pumpkin::Layer{
    void OnUpdate(float dt) override{
        PE_LOG_INFO("FPS: {}",  1/dt);
    }
};

class SandboxApp : public Pumpkin::Application{
    public:
        SandboxApp(){
            //custom ctor

            PushLayer(PE_MOVE_SCOPE(Pumpkin::CreateScope<SandboxLayer>()));
        }
};

Pumpkin::Application* Pumpkin::CreateApplication(){
    return new SandboxApp();
}