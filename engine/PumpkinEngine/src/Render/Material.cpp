#include "Render/Material.h"

#include <cstdint>

namespace Pumpkin{
    void Material::ApplyUniforms() const {
        if(!m_ShaderRef) return;
        
        uint32_t program = m_ShaderRef->ProgramID;

        for(const auto& [name, val] : m_Floats){
            int loc = glGetUniformLocation(program, name.c_str());
            if(loc != -1) glUniform1f(loc, val);
        }
    }
}