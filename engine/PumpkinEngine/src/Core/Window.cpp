#include "Core/Window.h"

#include "Core/Debug.h"
#include "Core/Log.h"
#include "Core/KeyCode.h"
#include "Event/InputEvent.h"
#include "Event/WindowEvent.h"

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

        SDL_PropertiesID propsID = SDL_GetWindowProperties(m_Window);
        SDL_SetPointerProperty(propsID, "PumpkinEngine.WindowData", &m_Data);
    }

    void Window::Shutdown(){
        if(m_Window){
            SDL_DestroyWindow(m_Window);
            m_Window = nullptr;
        }
    }

    void Window::OnUpdate(){
        EventUpdate();   
    }

    void Window::EventUpdate(){
        SDL_Event sdlEvent;

        const SDL_WindowID wndID = SDL_GetWindowID(m_Window);

        while(SDL_PollEvent(&sdlEvent)){
            if (sdlEvent.window.windowID != wndID) {
                continue;
            }

            //window
            if(sdlEvent.type == SDL_EVENT_WINDOW_RESIZED){
                m_Data.Width = sdlEvent.window.data1;
                m_Data.Height = sdlEvent.window.data2;

                WindowResizeEvent e(m_Data.Width, m_Data.Height);
                m_Data.EventCallback(e);
            }
            else if(sdlEvent.type == SDL_EVENT_QUIT || sdlEvent.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED){
                WindowCloseEvent e;
                m_Data.EventCallback(e);
            }
            
            //keyboard
            else if(sdlEvent.type == SDL_EVENT_KEY_DOWN){
                KeyCode key = static_cast<KeyCode>(sdlEvent.key.scancode);
                KeyPressedEvent e(key);
                m_Data.EventCallback(e);
            }
            else if(sdlEvent.type == SDL_EVENT_KEY_UP){
                KeyCode key = static_cast<KeyCode>(sdlEvent.key.scancode);
                KeyReleasedEvent e(key);
                m_Data.EventCallback(e);
            }
            
            //mouse
            else if(sdlEvent.type == SDL_EVENT_MOUSE_MOTION){
                MouseMovedEvent e(sdlEvent.motion.x, sdlEvent.motion.y);
                m_Data.EventCallback(e);
            }
            else if(sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                MouseButtonCode btn = static_cast<MouseButtonCode>(sdlEvent.button.button);
                MouseButtonPressedEvent e(btn);
                m_Data.EventCallback(e);
            }
            else if(sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_UP){
                MouseButtonCode btn = static_cast<MouseButtonCode>(sdlEvent.button.button);
                MouseButtonReleasedEvent e(btn);
                m_Data.EventCallback(e);
            }
            else if(sdlEvent.type == SDL_EVENT_MOUSE_WHEEL){
                MouseScrollEvent e(sdlEvent.wheel.x, sdlEvent.wheel.y);
                m_Data.EventCallback(e);
            }

        }
    }
}