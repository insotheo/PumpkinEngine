#ifndef PUMPKIN_ENGINE_KEY_CODE_H
#define PUMPKIN_ENGINE_KEY_CODE_H

#include <SDL3/SDL.h>
#include <cstdint>

namespace Pumpkin{
    using KeyCode = SDL_Keycode;
    using MouseButtonCode = uint8_t;
}

#endif