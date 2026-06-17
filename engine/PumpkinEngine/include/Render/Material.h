#ifndef PUMPKIN_ENGINE_MATERIAL_H
#define PUMPKIN_ENGINE_MATERIAL_H

#include "Render/Shader.h"
#include "Render/glad/gl.h"
#include <unordered_map>

namespace Pumpkin{
    class Material{
    public:
        Material(Shader* shader) : m_ShaderRef(shader) {}
        ~Material() = default;

        inline void SetShader(Shader* shader) { m_ShaderRef = shader; }
        inline Shader* GetShader() const { return m_ShaderRef; }

        inline void SetFloat(const std::string& name, float val) { m_Floats[name] = val; }

        void ApplyUniforms() const;

    private:
        Shader* m_ShaderRef = nullptr;
        std::unordered_map<std::string, float> m_Floats;
    };
}

#endif