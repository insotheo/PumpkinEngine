#include "Core/Application.h"

#include <SDL3/SDL.h>
#include "Core/Debug.h"
#include "Core/Window.h"

namespace Pumpkin{
    Application* Application::s_AppInst = nullptr;

    Application::Application(const ApplicationSpecification& specification)
    : m_Running(false), m_AppSpecification(specification)
    {
        PE_ASSERT(!s_AppInst, "Application can only be declared once");
        s_AppInst = this;

        if(!m_AppSpecification.Headless){
            m_Window = CreateScope<Window>(WindowProps { .Title = m_AppSpecification.Name });
            m_Window->SetEventCallback([this](auto& event) { OnEvent(event); });
        }
    }

    Application::~Application(){}

    void Application::Run(){
        m_Running = true;

        float deltaTime = 1.0/60.0;

        while(m_Running){
            //SDL events handling
            SDL_Event sdlEvent;
            while(SDL_PollEvent(&sdlEvent)){
                
            }

            //layers updating
            for(auto& layer : m_LayerStack)
                layer->OnUpdate(deltaTime);

            
            if(m_Window){
                //layers rendering
                for(auto& layer: m_LayerStack)
                    layer->OnRender();

                m_Window->OnUpdate();
            }
        }
    }

    void Application::OnEvent(Event& event){

    }
}