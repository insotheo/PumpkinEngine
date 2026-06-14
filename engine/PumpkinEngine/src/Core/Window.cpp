#include "Core/Window.h"
#include "Core/Debug.h"
#include "Core/Log.h"

namespace Pumpkin{
    Window::Window(const WindowProps& props) { Init(props); }
    Window::~Window() { Shutdown(); }

    void Window::Init(const WindowProps& props){
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        m_Data.Title = props.Title;

        if(!SDL_WasInit(SDL_INIT_VIDEO)){
            if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)){
                PE_LOG_ERROR("Could not initialize SDL3 video: {}", SDL_GetError());
                PE_ASSERT(false, "SDL3 init failed");
            }
        }

        m_Window = SDL_CreateWindow(
            m_Data.Title.c_str(),
            static_cast<int>(m_Data.Width),
            static_cast<int>(m_Data.Height),
            SDL_WINDOW_RESIZABLE
        );

        if(!m_Window){
            PE_LOG_ERROR("Could not create SDL3 window: {}", SDL_GetError());
            PE_ASSERT(false, "SDL3 window creation failed");
        }
    }

    void Window::Shutdown(){
        if(m_Window){
            SDL_DestroyWindow(m_Window);
            m_Window = nullptr;
        }
    }

    void Window::OnUpdate(){
        
    }
}