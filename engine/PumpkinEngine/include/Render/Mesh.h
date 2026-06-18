#ifndef PUMPKIN_ENGINE_RENDER_OBJECT_H
#define PUMPKIN_ENGINE_RENDER_OBJECT_H

#include "DefaultVertexLayouts.h"
#include <cstdint>

namespace Pumpkin{
    struct Mesh{
        uint32_t BlockIndex = 0;
        VertexLayoutType Type;
        uint32_t BaseVertex = 0;
        uint32_t FirstIndex = 0;
        uint32_t IndexCount = 0;
        uint32_t IndexType = 0;
    };
}

#endif 