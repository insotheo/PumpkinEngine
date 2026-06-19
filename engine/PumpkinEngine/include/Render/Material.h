#ifndef PUMPKIN_ENGINE_MATERIAL_H
#define PUMPKIN_ENGINE_MATERIAL_H

#include "Render/Shader.h"
#include "Thirdparty/glad/gl.h"
#include "Render/Texture.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace Pumpkin{
    class Material{
    public:
        Material(Shader* shader);
        ~Material();

        inline void SetShader(Shader* shader) { m_ShaderRef = shader; }
        inline Shader* GetShader() const { return m_ShaderRef; }

        void SetFloat(const std::string& name, float val);
        void SetVec2(const std::string& name, const glm::vec2& val);
        void SetTexture(const std::string& name, const Texture* val);

        void Bind(uint32_t bindingSlot = 1) const;

    private:
        Shader* m_ShaderRef = nullptr;
        MaterialUniforms_t* m_UniformsInfo = nullptr;

        uint32_t m_UBO = 0;
        std::vector<uint8_t> m_CpuBuffer;
    };
}

#endif