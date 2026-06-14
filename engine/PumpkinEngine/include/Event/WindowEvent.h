#ifndef PUMPKIN_ENGINE_WINDOW_EVENT_H
#define PUMPKIN_ENGINE_WINDOW_EVENT_H

#include "Event/Event.h"
#include <cstdint>
#include <format>

namespace Pumpkin{

    class WindowCloseEvent : public EventImpl<WindowCloseEvent>{
    public:
        inline std::string ToString() const override { return "Window close event"; }

    };

    class WindowResizeEvent : public EventImpl<WindowResizeEvent>{
    public:
        WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height)
        {}

        inline uint32_t GetWidth() const { return m_Width; }
        inline uint32_t GetHeight() const { return m_Height; }

        inline std::string ToString() const override { return std::format("Window resize event({};{})", m_Width, m_Height); }
    private:
        uint32_t m_Width, m_Height;
    };

}

#endif