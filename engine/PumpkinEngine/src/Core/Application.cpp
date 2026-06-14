#include "Core/Application.h"

#include "Core/Debug.h"

namespace Pumpkin{
    Application* Application::s_AppInst = nullptr;

    Application::Application()
    : m_Running(false)
    {
        PE_ASSERT(!s_AppInst, "Application can only be declared once");
        s_AppInst = this;
    }

    Application::~Application(){}

    void Application::Run(){
        m_Running = true;

        float deltaTime = 1.0/60.0;

        while(m_Running){

            //layers updating
            for(auto& layer : m_LayerStack){
                layer->OnUpdate(deltaTime);
            }

            //layers rendering
            for(auto& layer: m_LayerStack){
                layer->OnRender();
            }
        }
    }
}