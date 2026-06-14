#ifndef PUMPKIN_ENGINE_WINDOW_H
#define PUMPKIN_ENGINE_WINDOW_H

#include <string>
#include <cstdint>
#include <functional>
#include <SDL3/SDL.h>
#include "Event/Event.h"

namespace Pumpkin{

    struct WindowProps{
        std::string Title = "PumpkinEngine's Window";
        uint32_t Width = 800;
        uint32_t Height = 600;
    };

    class Window{
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        Window(const WindowProps& props);
        ~Window();

        void OnUpdate();

        inline uint32_t GetWidth() const { return m_Data.Width; };
        inline uint32_t GetHeight() const { return m_Data.Height; };

        inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

        inline SDL_Window* GetNative() const { return m_Window; }

    private:
        void Init(const WindowProps& props);
        void Shutdown();

        struct WindowData {
            std::string Title;
            uint32_t Width;
            uint32_t Height;
            EventCallbackFn EventCallback;
        };

        SDL_Window* m_Window = nullptr;
        WindowData m_Data;
    };
}

#endif