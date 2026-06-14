#include <PumpkinEngine.h>
#include <Event/InputEvent.h>
#include <Core/KeyCode.h>
#include <Core/Layer.h>
#include <Event/Event.h>

using namespace Pumpkin;

class SandboxLayer : public Layer{
    void OnEvent(Event& event) override{
        EventDispatcher inputDispatcher(event);

        inputDispatcher.Dispatch<KeyReleasedEvent>([&](KeyReleasedEvent& e){
            if(e.GetKeyCode() == KeyCode::Esc){
                Application::Get().Stop();
            }
        });
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