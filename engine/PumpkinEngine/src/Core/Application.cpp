#include "Core/Application.h"

#include <SDL3/SDL.h>
#include "Core/Base.h"
#include "Core/Debug.h"
#include "Core/Window.h"
#include "Event/Event.h"
#include "Event/WindowEvent.h"
#include "Render/Renderer.h"
#include "Render/Shader.h"
#include "Render/VertexLayout.h"

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
            
            m_Renderer = CreateScope<Renderer>();
            if(!m_Renderer->Initialize(m_Window->GetNative())){
                PE_ASSERT(false, "Failed to initialzie renderer");
            }
            m_Renderer->SetClearColor(1.f, 0.459f, 0.094f);
        }
        else{
            PE_ASSERT(false, "No headless mode yet");
        }
    }

    Application::~Application(){}

    void Application::Run(){
        m_Running = true;

        float deltaTime = 1.0/60.0;

        Shader* shader = m_Renderer->CreateShader("test.vert", "test.frag");
        
        Material triangleMat(shader);

        //TEST TRIANGLE
        float vertices[] = 
        {
            //x            y             z          r       g           b
            0.0f,   0.5f,   0.0f,   1.0f, 0.0f, 0.0f,   
            -0.5f,  -0.5f,  0.0f,   0.0f,1.0f,0.0f,
            0.5f,   -0.5f,  0.0f,0.0f, 0.0f, 1.0f,  
        };
        
        uint16_t indices[] = 
        {
            0u, 1u, 2u,
        };

        triangleMat.SetFloat("xOff", 0.5f);

        Mesh triangle = m_Renderer->AllocateMesh(vertices, indices,
            VertexLayout({
                VertexElement("inPos", ShaderDataType::Float3),
                VertexElement("inColor", ShaderDataType::Float3)
            })
        );

        while(m_Running){
            //layers updating
            for(auto& layer : m_LayerStack)
                layer->OnUpdate(deltaTime);

            
            if(m_Window){
                m_Window->OnUpdate(); //events

                m_Renderer->Clear();

                //TEST
                m_Renderer->DrawObject(triangle, triangleMat);

                //layers rendering
                for(auto& layer: m_LayerStack)
                    layer->OnRender();
        
                m_Renderer->Present();
            }
            else{ //headless
                SDL_Delay(1);
            }
        }

        shader->Shutdown();
    }

    void Application::OnEvent(Event& event){
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& closeEvent){ Stop(); });

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ){
            (*--it)->OnEvent(event);
            if(event.Handled) break;
        }
    }
}