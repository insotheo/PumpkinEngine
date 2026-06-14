#ifndef PUMPKIN_ENGINE_WINDOW_EVENT_H
#define PUMPKIN_ENGINE_WINDOW_EVENT_H

#include "Event/Event.h"
#include <format>

namespace Pumpkin{

    class WindowClose : public EventImpl<WindowClose>{
    public:
        inline std::string ToString() const override { return "Window close event"; }

    };

    class WindowResize : public EventImpl<WindowResize>{
    public:
        WindowResize(int width, int height) : m_Width(width), m_Height(height)
        {}

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

        inline std::string ToString() const override { return std::format("Window resize event({};{})", m_Width, m_Height); }
    private:
        int m_Width, m_Height;
    };

}

#endif