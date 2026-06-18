#include "Render/VertexLayout.h"

namespace Pumpkin{
    VertexLayout::VertexLayout(const std::initializer_list<VertexElement>& elements) : m_Elements(elements){
        uint32_t currentOffset = 0;
        uint32_t currentLocation = 0;

        for(auto& el : m_Elements){
            el.m_Offset = currentOffset;
            el.m_Location = currentLocation;

            uint32_t size = GetTypeSize(el.GetType());
            currentOffset += size;
            currentLocation++;
        }

        m_Stride = currentOffset;
    }
}