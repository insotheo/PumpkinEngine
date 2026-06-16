#ifndef PUMPKIN_ENGINE_MATERIAL_H
#define PUMPKIN_ENGINE_MATERIAL_H

#include <SDL3/SDL.h>

namespace Pumpkin{
    struct Material{
        SDL_GPUGraphicsPipeline* Pipeline = nullptr;
    };
}

#endif