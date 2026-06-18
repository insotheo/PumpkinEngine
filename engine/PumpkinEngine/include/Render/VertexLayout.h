#ifndef PUMPKIN_ENGINE_VERTEX_LAYOUT_H
#define PUMPKIN_ENGINE_VERTEX_LAYOUT_H

#include "Core/Debug.h"
#include "Render/glad/gl.h"
#include <cstdint>
#include <initializer_list>
#include <vector>
#include <string>

namespace Pumpkin{
    enum class ShaderDataType{
        None = 0,
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat3, Mat4,
        Bool
    };

    class VertexElement{
        friend class VertexLayout;
    public:
        VertexElement(const std::string& name, ShaderDataType type) : m_Name(name), m_Type(type)
        {}
        
        inline const std::string& GetName() const { return m_Name; }
        inline ShaderDataType GetType() const { return m_Type; }
        inline uint32_t GetOffset() const { return m_Offset; }
        inline uint32_t GetLocation() const { return m_Location; }

        inline uint32_t GetComponentCount() const {
            switch(m_Type){
                case ShaderDataType::Float:
                case ShaderDataType::Int:
                case ShaderDataType::Bool:
                    return 1;
                
                case ShaderDataType::Float2:
                case ShaderDataType::Int2:
                    return 2;

                case ShaderDataType::Float3:
                case ShaderDataType::Int3:
                    return 3;

                case ShaderDataType::Float4:
                case ShaderDataType::Int4:
                    return 4;

                case ShaderDataType::Mat3: return 3 * 3;
                case ShaderDataType::Mat4: return 4 * 4;

                default:{
                    PE_ASSERT(false, "Unknown shader data type!");
                    return 0;
                }
            }
        }

        inline GLenum GetOpenGLType() const {
            switch(m_Type){
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                    return GL_FLOAT;

                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                    return GL_INT;

                case ShaderDataType::Bool:
                    return GL_BOOL;

                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                    return GL_MATRIX_STRIDE;

                default:{
                    PE_ASSERT(false, "Unknown shader data type!");
                    return 0;
                }
            }
        }

    private:
        std::string m_Name;
        ShaderDataType m_Type;
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
        static uint32_t GetTypeSize(ShaderDataType type){
            switch(type){
                case ShaderDataType::Bool: return 1;

                case ShaderDataType::Float:
                case ShaderDataType::Int:
                    return 4;

                case ShaderDataType::Float2:
                case ShaderDataType::Int2:
                    return 4 * 2;
                    
                case ShaderDataType::Float3:
                case ShaderDataType::Int3:
                    return 4 * 3;

                case ShaderDataType::Float4:
                case ShaderDataType::Int4:
                    return 4 * 4;

                case ShaderDataType::Mat3: return 3 * 3 * 4;
                case ShaderDataType::Mat4: return 4 * 4 * 4;

                default:{
                    PE_ASSERT(false, "Unknown shader data type!");
                    return 0;
                }
            }
        }
        
        std::vector<VertexElement> m_Elements;
        uint32_t m_Stride = 0;
    };
}

#endif