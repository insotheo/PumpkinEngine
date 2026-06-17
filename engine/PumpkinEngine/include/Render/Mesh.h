#ifndef PUMPKIN_ENGINE_RENDER_OBJECT_H
#define PUMPKIN_ENGINE_RENDER_OBJECT_H

#include <SDL3/SDL.h>
#include <cstdint>

namespace Pumpkin{
    struct Mesh{
        uint32_t VertexOffsetBytes = 0;
        uint32_t IndexOffsetBytes = 0;
        uint32_t IndexCount = 0;
        SDL_GPUIndexElementSize IndexElementSize = SDL_GPU_INDEXELEMENTSIZE_32BIT;
    };
}

#endif 