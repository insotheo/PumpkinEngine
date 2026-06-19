#ifndef PUMPKIN_ENGINE_DEFAULT_VERTEX_LAYOUTS_H
#define PUMPKIN_ENGINE_DEFAULT_VERTEX_LAYOUTS_H

#include <cstdint>
#include <glm/glm.hpp>

namespace Pumpkin{
    enum class VertexLayoutType : uint8_t{
        Simple2D = 0,
        Default3D = 1,
    };
}

#endif