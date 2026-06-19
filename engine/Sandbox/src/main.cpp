#include <PumpkinEngine.h>
#include <Core/Input.h>
#include <Core/Layer.h>

using namespace Pumpkin;

class SandboxLayer : public Layer{
    void OnUpdate(float dt) override{
        if(Input::IsKeyReleased(KeyCode::Esc) || Input::IsMouseButtonReleased(MouseButtonCode::Middle)){
            Application::Get().Stop();
        }
    }
};

class SandboxApp : public Application{
    public:
        SandboxApp(){
            //custom ctor

            PushLayer(PE_MOVE_SCOPE(CreateScope<SandboxLayer>()));
        }
};

Pumpkin::Application* Pumpkin::CreateApplication(){
    return new SandboxApp();
}