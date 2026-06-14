#include <PumpkinEngine.h>
#include <Event/Event.h>
#include <Event/InputEvent.h>

class SandboxApp : public Pumpkin::Application{
    public:
        SandboxApp(){
            //custom ctor
        }
};

Pumpkin::Application* Pumpkin::CreateApplication(){
    return new SandboxApp();
}