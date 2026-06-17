#ifndef PUMPKIN_ENGINE_SHADER_H
#define PUMPKIN_ENGINE_SHADER_H

#include <SDL3/SDL.h>
#include "Render/VertexLayout.h"

namespace Pumpkin{
    struct Shader{
        SDL_GPUShader* Vertex = nullptr;
        SDL_GPUShader* Fragment = nullptr;
        VertexLayout Layout;
    };
}

#endif