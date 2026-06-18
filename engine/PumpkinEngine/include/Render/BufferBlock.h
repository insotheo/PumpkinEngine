#ifndef PUMPKIN_ENGINE_BUFFER_BLOCK_H
#define PUMPKIN_ENGINE_BUFFER_BLOCK_H

#include <cstdint>

namespace Pumpkin{
    struct BufferBlock{
        uint32_t VBO = 0;
        uint32_t EBO = 0;

        uint32_t VAOs[2] = {0, 0};

        uint32_t CapacityVBO = 0;
        uint32_t CapacityEBO = 0;

        uint32_t OffsetVBO = 0;
        uint32_t OffsetEBO = 0;

        uint8_t* VboPtr = nullptr;
        uint8_t* EboPtr = nullptr;
    };
}

#endif