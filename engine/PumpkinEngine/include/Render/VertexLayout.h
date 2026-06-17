#ifndef PUMPKIN_ENGINE_VERTEX_LAYOUT_H
#define PUMPKIN_ENGINE_VERTEX_LAYOUT_H

#include <SDL3/SDL.h>
#include <cstdint>
#include <initializer_list>
#include <vector>
#include <string>

#define PE_VERTEX_EL_FORMAT(identifier) SDL_GPU_VERTEXELEMENTFORMAT_##identifier

namespace Pumpkin{
    class VertexElement{
        friend class VertexLayout;
    public:
        VertexElement(const std::string& name, SDL_GPUVertexElementFormat format) : m_Name(name), m_Format(format)
        {}
        
        inline const std::string& GetName() const { return m_Name; }
        inline SDL_GPUVertexElementFormat GetFormat() const { return m_Format; }
        inline uint32_t GetOffset() const { return m_Offset; }
        inline uint32_t GetLocation() const { return m_Location; }

        inline uint32_t GetComponentCount() const {
            switch(m_Format){
                case SDL_GPU_VERTEXELEMENTFORMAT_FLOAT: return 1;
                case SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2: return 2;
                case SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3: return 3;
                case SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4: return 4;
                default: return 0;
            }
        }

    private:
        std::string m_Name;
        SDL_GPUVertexElementFormat m_Format;
        uint32_t m_Offset;
        uint32_t m_Location;
    };

    class VertexLayout{
    public:
        VertexLayout() = default;
        VertexLayout(const std::initializer_list<VertexElement>& elements);

        inline const std::vector<VertexElement>& GetElements() const { return m_Elements; }
        inline uint32_t GetStride() const { return m_Stride; } 

    private:
        static uint32_t GetFormatSize(SDL_GPUVertexElementFormat format){
            switch(format){
                case SDL_GPU_VERTEXELEMENTFORMAT_INT: return 4;
                case SDL_GPU_VERTEXELEMENTFORMAT_INT2: return 4 * 2;
                case SDL_GPU_VERTEXELEMENTFORMAT_INT3: return 4 * 3;
                case SDL_GPU_VERTEXELEMENTFORMAT_INT4: return 4 * 4;

                case SDL_GPU_VERTEXELEMENTFORMAT_UINT: return 4;
                case SDL_GPU_VERTEXELEMENTFORMAT_UINT2: return 4 * 2;
                case SDL_GPU_VERTEXELEMENTFORMAT_UINT3: return 4 * 3;
                case SDL_GPU_VERTEXELEMENTFORMAT_UINT4: return 4 * 4;
                
                case SDL_GPU_VERTEXELEMENTFORMAT_FLOAT: return 4;
                case SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2: return 4 * 2;
                case SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3: return 4 * 3;
                case SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4: return 4 * 4;
                
                case SDL_GPU_VERTEXELEMENTFORMAT_BYTE2: return 1 * 2;
                case SDL_GPU_VERTEXELEMENTFORMAT_BYTE4: return 1 * 4;

                case SDL_GPU_VERTEXELEMENTFORMAT_UBYTE2: return 1 * 2;
                case SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4: return 1 * 4;
                
                case SDL_GPU_VERTEXELEMENTFORMAT_SHORT2: return 2 * 2;
                case SDL_GPU_VERTEXELEMENTFORMAT_SHORT4: return 2 * 4;                
                
                case SDL_GPU_VERTEXELEMENTFORMAT_USHORT2: return 2 * 2;
                case SDL_GPU_VERTEXELEMENTFORMAT_USHORT4: return 2 * 4;

                case SDL_GPU_VERTEXELEMENTFORMAT_HALF2: return 4;
                case SDL_GPU_VERTEXELEMENTFORMAT_HALF4: return 8;

                default: return 0;
            }
            return 0;
        }
        
        std::vector<VertexElement> m_Elements;
        uint32_t m_Stride = 0;
    };
}

#endif