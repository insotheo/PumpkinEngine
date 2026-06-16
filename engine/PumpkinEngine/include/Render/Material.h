#ifndef PUMPKIN_ENGINE_MATERIAL_H
#define PUMPKIN_ENGINE_MATERIAL_H

#include "Render/Shader.h"

namespace Pumpkin{
    struct Material{
        Shader* ShaderRef = nullptr;
    };
}

#endif