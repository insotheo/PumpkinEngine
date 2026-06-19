#include "Core/Input.h"

namespace Pumpkin{
    std::array<bool, 512> Input::s_KeyPressed {};
    std::array<bool, 512> Input::s_KeyReleased {};   
    std::array<bool, 5> Input::s_MouseBtnPressed {};
    std::array<bool, 5> Input::s_MouseBtnReleased {};
    glm::vec2 Input::s_MousePos {};
    glm::vec2 Input::s_MouseWheel {};
}