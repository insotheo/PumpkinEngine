#ifndef PUMPKIN_ENGINE_INPUT_H
#define PUMPKIN_ENGINE_INPUT_H

#include "Core/KeyCode.h"
#include <cstddef>
#include <array>
#include <glm/glm.hpp>

namespace Pumpkin{
    class Application;
    class Window;

    class Input{
        friend class Application;
        friend class Window;

    public:
        inline static bool IsKeyPressed(KeyCode key) { return s_KeyPressed[static_cast<size_t>(key)]; }    
        inline static bool IsKeyReleased(KeyCode key) { return s_KeyReleased[static_cast<size_t>(key)]; }            
        inline static bool IsMouseButtonPressed(MouseButtonCode button) { return s_MouseBtnPressed[static_cast<size_t>(button)]; }    
        inline static bool IsMouseButtonReleased(MouseButtonCode button) { return s_MouseBtnReleased[static_cast<size_t>(button)]; }    
        inline static const glm::vec2 GetMousePosition() { return s_MousePos; }
        inline static const glm::vec2 GetMouseWheelOffset() { return s_MouseWheel; }

    private:
        static void Init(){
            s_KeyPressed.fill(false);
            s_KeyReleased.fill(false);
            s_MouseBtnPressed.fill(false);
            s_MouseBtnReleased.fill(false);
        }
        static void Update(){
            s_KeyReleased.fill(false);
            s_MouseBtnReleased.fill(false);
            s_MouseWheel = {0.f,0.f};
        }

        inline static void SetKeyPressed(KeyCode key, bool state) { s_KeyPressed[static_cast<size_t>(key)] = state; }
        inline static void SetKeyReleased(KeyCode key, bool state) { s_KeyReleased[static_cast<size_t>(key)] = state; }       
        inline static void SetMouseButtonPressed(MouseButtonCode button, bool state) { s_MouseBtnPressed[static_cast<size_t>(button)] = state; }
        inline static void SetMouseButtonReleased(MouseButtonCode button, bool state) { s_MouseBtnReleased[static_cast<size_t>(button)] = state; }
        inline static void SetMousePosition(float x, float y) { s_MousePos = {x, y}; }
        inline static void SetMouseWheel(float xOff, float yOff) { s_MouseWheel = {xOff, yOff}; }

        static std::array<bool, 512> s_KeyPressed;
        static std::array<bool, 512> s_KeyReleased;        
        static std::array<bool, 5> s_MouseBtnPressed;
        static std::array<bool, 5> s_MouseBtnReleased;
        static glm::vec2 s_MousePos;
        static glm::vec2 s_MouseWheel;
    };
}

#endif