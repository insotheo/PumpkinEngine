#ifndef PUMPKIN_ENGINE_SHADER_H
#define PUMPKIN_ENGINE_SHADER_H

#include <SDL3/SDL.h>
#include <cstdint>
#include <string>
#include "Render/glad/gl.h"

namespace Pumpkin{
    class Shader{
    public:
        Shader() = default;
        ~Shader();

        bool LoadFromFile(const std::string& vertexPath, const std::string& fragmentPath);
        void Shutdown();

        uint32_t ProgramID = 0;

    private:
        std::string ReadFile(const std::string& path);
        uint32_t CompileStage(const std::string& sorce, GLenum stageType);
    };
}

#endif