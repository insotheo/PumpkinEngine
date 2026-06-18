#include "Render/Shader.h"

#include "Core/Log.h"
#include <vector>
#include <fstream>
#include <sstream>

namespace Pumpkin{
    Shader::~Shader() { Shutdown(); }

    void Shader::Shutdown(){
        if(ProgramID != 0){
            glDeleteProgram(ProgramID);
            ProgramID = 0;
        }
    }

    std::string Shader::ReadFile(const std::string& path){
        std::ifstream file(path);
        if(!file.is_open()){
            PE_LOG_ERROR("Shader: failed to open file at {}", path);
            return "";
        }

        std::stringstream stream;
        stream << file.rdbuf();
        return stream.str();
    }

    uint32_t Shader::CompileStage(const std::string& source, GLenum stageType){
        if(source.empty()) return 0;

        uint32_t shaderID = glCreateShader(stageType);
        const char* srcPtr = source.c_str();
        glShaderSource(shaderID, 1, &srcPtr, nullptr);
        glCompileShader(shaderID);

        int success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if(!success){
            int logLength;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<char> infoLog(logLength);
            glGetShaderInfoLog(shaderID, logLength, nullptr, infoLog.data());

            std::string stageName = (stageType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
            PE_LOG_ERROR("Shader: {} compilation failed!\n{}", stageName, infoLog.data());
            glDeleteShader(shaderID);
            return 0;
        }
        return shaderID;
    }

    bool Shader::LoadFromFile(const std::string& vertexPath, const std::string& fragmentPath){
        std::string vertexSource = ReadFile(vertexPath);
        std::string fragmentSource = ReadFile(fragmentPath);

        uint32_t vertexShader = CompileStage(vertexSource, GL_VERTEX_SHADER);
        uint32_t fragmentShader = CompileStage(fragmentSource, GL_FRAGMENT_SHADER);

        ProgramID = glCreateProgram();
        glAttachShader(ProgramID, vertexShader);
        glAttachShader(ProgramID, fragmentShader);
        glLinkProgram(ProgramID);

        int success;
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
        if(!success){
            int logLength;
            glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<char> infoLog(logLength);
            glGetProgramInfoLog(ProgramID, logLength, nullptr, infoLog.data());
            PE_LOG_ERROR("Shader: Linking failed!\n{}", infoLog.data());
            Shutdown();
            return 0;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return ProgramID;
    }
}