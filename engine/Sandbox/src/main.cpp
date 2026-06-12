#include <PumpkinEngine.h>

class SandboxApp : public Pumpkin::Application{
    public:
        SandboxApp(){
            //custom ctor
        }
};

Pumpkin::Application* Pumpkin::CreateApplication(){
    return new SandboxApp();
}