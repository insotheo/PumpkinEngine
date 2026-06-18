#include "Render/Shader.h"

#include "Core/Log.h"
#include <cstdint>
#include <vector>
#include <fstream>
#include <sstream>

namespace Pumpkin{
    Shader::~Shader() { Shutdown(); }

    void Shader::Shutdown(){
        if(m_ProgramID != 0){
            glDeleteProgram(m_ProgramID);
            m_ProgramID = 0;
        }
        m_MaterialUniforms.clear();
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

        m_ProgramID = glCreateProgram();
        glAttachShader(m_ProgramID, vertexShader);
        glAttachShader(m_ProgramID, fragmentShader);
        glLinkProgram(m_ProgramID);

        int success;
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
        if(!success){
            int logLength;
            glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<char> infoLog(logLength);
            glGetProgramInfoLog(m_ProgramID, logLength, nullptr, infoLog.data());
            PE_LOG_ERROR("Shader: Linking failed!\n{}", infoLog.data());
            Shutdown();
            return 0;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        ReflectMaterialBlock();

        return m_ProgramID;
    }

    void Shader::ReflectMaterialBlock(){
        uint32_t blockIdx = glGetUniformBlockIndex(m_ProgramID, "Material");
        if(blockIdx == GL_INVALID_INDEX) return;

        glGetActiveUniformBlockiv(m_ProgramID, blockIdx, GL_UNIFORM_BLOCK_DATA_SIZE, (int*)&m_MaterialBufferSize);

        int uniformCount = 0;
        glGetActiveUniformBlockiv(m_ProgramID, blockIdx, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &uniformCount);
        
        std::vector<int> uniformIndices(uniformCount);
        glGetActiveUniformBlockiv(m_ProgramID, blockIdx, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, uniformIndices.data());
        
        std::vector<int> offsets(uniformCount);
        glGetActiveUniformsiv(m_ProgramID, uniformCount, (uint32_t*)uniformIndices.data(), GL_UNIFORM_OFFSET, offsets.data());
        
        std::vector<int> sizes(uniformCount);
        glGetActiveUniformsiv(m_ProgramID, uniformCount, (uint32_t*)uniformIndices.data(), GL_UNIFORM_SIZE, sizes.data());

        for(int i = 0; i < uniformCount; ++i){
            char name[256];
            GLsizei length;
            glGetActiveUniformName(m_ProgramID, uniformIndices[i], sizeof(name), &length, name);

            std::string uniformName(name);
            size_t dotPos = uniformName.find('.');
            if(dotPos != std::string::npos){
                uniformName = uniformName.substr(dotPos + 1);
            }

            UniformInfo info;
            info.Offset = static_cast<uint32_t>(offsets[i]);
            info.Size = static_cast<uint32_t>(sizes[i]);

            m_MaterialUniforms[uniformName] = info;
        }
    }
}