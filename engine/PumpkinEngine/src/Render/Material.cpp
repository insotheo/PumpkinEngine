#include "Render/Material.h"

#include <cstring>
#include <cstdint>
#include <glm/gtc/type_ptr.hpp>

#define GEN_MATERIAL_SET_FN(MethodName, ArgDataType, DataType, ValForm, HandleCreation)\
    void Material::Set##MethodName(const std::string& name, ArgDataType val){\
        if(!m_UniformsInfo) return;\
        auto it = m_UniformsInfo->find(name);\
        if(it != m_UniformsInfo->end()){\
            HandleCreation;\
            std::memcpy(m_CpuBuffer.data() + it->second.Offset, ValForm, sizeof(DataType));\
        }\
    }

namespace Pumpkin{
    Material::Material(Shader* shader) : m_ShaderRef(shader)
    {
        if(m_ShaderRef){
            m_UniformsInfo = m_ShaderRef->GetMaterialUniformsPtr();

            uint32_t rawSize = m_ShaderRef->GetMaterialBufferSize();
            uint32_t alignedSize = (rawSize + 15) & ~15;

            m_CpuBuffer.resize(alignedSize, 0);

            glCreateBuffers(1, &m_UBO);
            glNamedBufferStorage(m_UBO, m_CpuBuffer.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
        }
    }

    Material::~Material(){
        if(m_UBO != 0) glDeleteBuffers(1, &m_UBO);
        m_ShaderRef = nullptr;
        m_UniformsInfo = nullptr;
    }

    void Material::Bind(uint32_t bindingSlot) const {
        if(m_UBO == 0 || m_CpuBuffer.empty()) return;
        
        glNamedBufferSubData(m_UBO, 0, m_CpuBuffer.size(), m_CpuBuffer.data());
        glBindBufferBase(GL_UNIFORM_BUFFER, bindingSlot, m_UBO);
    }

    GEN_MATERIAL_SET_FN(Float, float, float, &val, )
    GEN_MATERIAL_SET_FN(Vec2, const glm::vec2&, glm::vec2, glm::value_ptr(val), )
    GEN_MATERIAL_SET_FN(Texture, const Texture*, uint64_t, &handle, uint64_t handle = val->GetHandle())
}