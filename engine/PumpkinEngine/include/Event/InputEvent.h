#ifndef PUMPKIN_ENGINE_INPUT_EVENT_H
#define PUMPKIN_ENGINE_INPUT_EVENT_H

#include "Event/Event.h"
#include "Core/KeyCode.h"
#include <format>

namespace Pumpkin{
    
    class KeyPressedEvent : public EventImpl<KeyPressedEvent>{
    public:
        KeyPressedEvent(KeyCode code) : m_Code(code)
        {}

        inline KeyCode GetKeyCode() const { return m_Code; }

        inline std::string ToString() const override { return std::format("Key pressed event(code: {})", static_cast<uint32_t>(m_Code)); }

    private:
        KeyCode m_Code;
    };

    class KeyReleasedEvent : public EventImpl<KeyReleasedEvent>{
    public:
        KeyReleasedEvent(KeyCode code) : m_Code(code)
        {}

        inline KeyCode GetKeyCode() const { return m_Code; }

        inline std::string ToString() const override { return std::format("Key released event(code: {})", static_cast<uint32_t>(m_Code)); }

    private:
        KeyCode m_Code;
    };

    class MouseMovedEvent : public EventImpl<MouseMovedEvent>{
    public:
        MouseMovedEvent(float x, float y) : m_X(x), m_Y(y)
        {}

        inline float GetX() const { return m_X; }
        inline float GetY() const { return m_Y; }

        inline std::string ToString() const override { return std::format("Mouse move event({};{})", m_X, m_Y); }

    private:
        float m_X, m_Y;
    };

    class MouseButtonPressedEvent : public EventImpl<MouseButtonPressedEvent>{
    public:
        MouseButtonPressedEvent(MouseButtonCode btn) : m_Btn(btn)
        {}

        inline MouseButtonCode GetMouseButton() const { return m_Btn; }

        inline std::string ToString() const override { return std::format("Mouse button pressed event(code: {})", m_Btn); }

    private:
        MouseButtonCode m_Btn;
    };

    class MouseButtonReleasedEvent : public EventImpl<MouseButtonReleasedEvent>{
    public:
        MouseButtonReleasedEvent(MouseButtonCode btn) : m_Btn(btn)
        {}

        inline MouseButtonCode GetMouseButton() const { return m_Btn; }

        inline std::string ToString() const override { return std::format("Mouse button released event(code: {})", m_Btn); }

    private:
        MouseButtonCode m_Btn;
    };

    class MouseScrollEvent : public EventImpl<MouseScrollEvent>{
    public:
        MouseScrollEvent(float xOff, float yOff) : m_XOff(xOff), m_YOff(yOff)
        {}

        inline float GetXOffset() const { return m_XOff; }
        inline float GetYOffset() const { return m_YOff; }

        inline std::string ToString() const override { return std::format("Mouse scroll event({};{})", m_XOff, m_YOff); }

    private:
        float m_XOff, m_YOff;
    };

}

#endif