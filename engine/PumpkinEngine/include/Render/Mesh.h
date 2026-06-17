#ifndef PUMPKIN_ENGINE_RENDER_OBJECT_H
#define PUMPKIN_ENGINE_RENDER_OBJECT_H

#include <cstdint>

namespace Pumpkin{
    struct Mesh{
        uint32_t VAO = 0;
        uint32_t VBO = 0;
        uint32_t EBO = 0;
        uint32_t IndexCount = 0;
    };
}

#endif 