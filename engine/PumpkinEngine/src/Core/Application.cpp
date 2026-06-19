#include "Core/Application.h"

#include <SDL3/SDL.h>
#include <chrono>
#include "Core/Base.h"
#include "Core/Debug.h"
#include "Core/Window.h"
#include "Event/Event.h"
#include "Core/Input.h"
#include "Event/WindowEvent.h"
#include "Render/Renderer.h"
#include "Render/Shader.h"
#include "Render/Texture.h"

namespace Pumpkin{
    Application* Application::s_AppInst = nullptr;

    Application::Application(const ApplicationSpecification& specification)
    : m_Running(false), m_AppSpecification(specification)
    {
        PE_ASSERT(!s_AppInst, "Application can only be declared once");
        s_AppInst = this;

        if(!m_AppSpecification.Headless){
            Input::Init();

            m_Window = CreateScope<Window>(WindowProps { .Title = m_AppSpecification.Name });
            m_Window->SetEventCallback([this](auto& event) { OnEvent(event); });
            
            m_Renderer = CreateScope<Renderer>();
            if(!m_Renderer->Initialize(m_Window.get())){
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
        auto lastTime = std::chrono::high_resolution_clock::now();

        Shader* shader = m_Renderer->CreateShader("test.vert", "test.frag");
        Texture* texture = new Texture("myCat.jpg");
        
        Material triangleMat(shader);

        //TEST TRIANGLE
        float vertices[] = 
        {
                //x          y          u         v       
            -1.0f,  1.0f,  0.0f, 0.0f,
            -1.0f, -1.0f,  0.0f, 1.0f,
             1.0f, -1.0f, 1.0f,1.0f,
            1.0f, 1.0f, 1.0f,0.0f
        };
        
        uint16_t indices[] = 
        {
            0u, 1u, 2u,
            2u, 3u, 0u
        };

        glm::vec2 offset{0.f, 0.f};
        float velocity = 0.5f;
        triangleMat.SetFloat("u_Scale", 0.75f);
        triangleMat.SetTexture("u_Texture", texture);

        Mesh triangle = m_Renderer->AllocateMesh(vertices, indices, VertexLayoutType::Simple2D);

        while(m_Running){
            auto currentTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
            lastTime = currentTime;
            if(deltaTime > 0.1) deltaTime = 0.1;
            
            //TEST
            if(Input::IsKeyPressed(KeyCode::W)) offset.y += 1.f;
            else if(Input::IsKeyPressed(KeyCode::S)) offset.y -= 1.f;
            else if(Input::IsKeyPressed(KeyCode::D)) offset.x += 1.f;
            else if(Input::IsKeyPressed(KeyCode::A)) offset.x -= 1.f;

            triangleMat.SetVec2("u_Offset", offset * velocity * deltaTime);

            if(m_Window){
                Input::Update();

                m_Window->OnUpdate(); //events

                m_Renderer->Clear();

                //TEST
                m_Renderer->DrawObject(triangle, triangleMat);

                //layers rendering
                for(auto& layer: m_LayerStack)
                    layer->OnRender();
        
                m_Renderer->Present();
            }

            //layers updating
            for(auto& layer : m_LayerStack)
                layer->OnUpdate(deltaTime);

            if(!m_Window) SDL_Delay(1);
        }

        shader->Shutdown();
        delete texture;
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