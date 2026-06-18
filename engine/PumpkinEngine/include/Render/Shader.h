#ifndef PUMPKIN_ENGINE_SHADER_H
#define PUMPKIN_ENGINE_SHADER_H

#include <SDL3/SDL.h>
#include <cstdint>
#include <string>
#include <unordered_map>
#include "Render/glad/gl.h"


namespace Pumpkin{
    struct UniformInfo{
        uint32_t Offset;
        uint32_t Size;
    };

    typedef std::unordered_map<std::string, UniformInfo> MaterialUniforms_t; 

    class Shader{
    public:
        Shader() = default;
        ~Shader();

        inline uint32_t GetProgramID() const { return m_ProgramID; }
        inline MaterialUniforms_t* GetMaterialUniformsPtr() { return &m_MaterialUniforms; }
        inline uint32_t GetMaterialBufferSize() const { return m_MaterialBufferSize; }

        bool LoadFromFile(const std::string& vertexPath, const std::string& fragmentPath);
        void Shutdown();

    private:
        uint32_t m_ProgramID = 0;
        MaterialUniforms_t m_MaterialUniforms;
        uint32_t m_MaterialBufferSize = 0;

        void ReflectMaterialBlock();
        std::string ReadFile(const std::string& path);
        uint32_t CompileStage(const std::string& sorce, GLenum stageType);
    };
}

#endif