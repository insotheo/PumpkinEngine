#include <PumpkinEngine.h>
#include <Event/Event.h>
#include <Event/InputEvent.h>

class SandboxApp : public Pumpkin::Application{
    public:
        SandboxApp(){
            //custom ctor

            PE_LOG_INFO("Hello!");

            Pumpkin::KeyPressedEvent e(Pumpkin::KeyCode::M);

            Pumpkin::EventDispatcher dispatcher(e);
            dispatcher.Dispatch<Pumpkin::KeyPressedEvent>([this](Pumpkin::KeyPressedEvent& ev){
                std::cout << (char)ev.GetKeyCode() << "\n";
            });
        }
};

Pumpkin::Application* Pumpkin::CreateApplication(){
    return new SandboxApp();
}