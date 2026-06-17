#include "Render/Renderer.h"

#include "Core/Debug.h"
#include "Core/Log.h"
#include "Render/Shader.h"
#include <cstdint>
#include <fstream>
#include <vector>

namespace Pumpkin{
    
    SDL_GPUShader* Renderer::LoadShaderStage(const std::string& path, SDL_GPUShaderStage stage){
        std::ifstream file(path, std::ios::ate | std::ios::binary);
        if(!file.is_open()){
            PE_LOG_ERROR("Renderer: failed to open shader file: {}", path);
            return nullptr;
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();

        SDL_GPUShaderCreateInfo shaderInfo;
        SDL_zero(shaderInfo);
        shaderInfo.code_size = fileSize;
        shaderInfo.code = reinterpret_cast<const uint8_t*>(buffer.data());
        shaderInfo.entrypoint = "main";
        shaderInfo.format = SDL_GPU_SHADERFORMAT_SPIRV; //TODO: other types
        shaderInfo.stage = stage;

        return SDL_CreateGPUShader(m_Device, &shaderInfo);
    }

    Shader* Renderer::CreateShader(const std::string& vertPath, const std::string& fragPath, const VertexLayout& layout){
        SDL_GPUShader* vertShader = LoadShaderStage(vertPath, SDL_GPU_SHADERSTAGE_VERTEX);
        SDL_GPUShader* fragShader = LoadShaderStage(fragPath, SDL_GPU_SHADERSTAGE_FRAGMENT);

        if(!vertShader || !fragShader){
            PE_ASSERT(false, "Failed to load shaders!");
            return nullptr;
        }

        Shader* shader = new Shader();
        shader->Vertex = vertShader;
        shader->Fragment = fragShader;
        shader->Layout = layout;

        return shader;
    }

    void Renderer::DestroyShader(Shader* shader){
        if(!shader) return;

        for(auto it = m_PipelineCache.begin(); it != m_PipelineCache.end();){
            if(it->first.shader == shader){
                SDL_ReleaseGPUGraphicsPipeline(m_Device, it->second);
                it = m_PipelineCache.erase(it);
            }
            else{
                ++it;
            }
        }

        SDL_ReleaseGPUShader(m_Device, shader->Vertex);
        SDL_ReleaseGPUShader(m_Device, shader->Fragment);

        delete shader;
    }

    SDL_GPUGraphicsPipeline* Renderer::GetOrCreatePipeline(Shader* shader){
        PipelineKey key = {shader };

        auto it = m_PipelineCache.find(key);
        if(it != m_PipelineCache.end()){
            return it->second;
        }

        const VertexLayout& layout = shader->Layout;
        const auto& layoutElements = layout.GetElements();

        std::vector<SDL_GPUVertexAttribute> sdlAttribs(layoutElements.size());
        for(size_t i = 0; i < layoutElements.size(); ++i){
            SDL_zero(sdlAttribs[i]);
            sdlAttribs[i].location = layoutElements[i].GetLocation();
            sdlAttribs[i].buffer_slot = 0;
            sdlAttribs[i].format = layoutElements[i].GetFormat();
            sdlAttribs[i].offset = layoutElements[i].GetOffset();
        }

        SDL_GPUVertexBufferDescription buffDesc;
        SDL_zero(buffDesc);
        buffDesc.slot = 0;
        buffDesc.pitch = layout.GetStride();
        buffDesc.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;

        SDL_GPUGraphicsPipelineCreateInfo pInfo;
        SDL_zero(pInfo);
        pInfo.vertex_shader = shader->Vertex;
        pInfo.fragment_shader = shader->Fragment;

        pInfo.vertex_input_state.vertex_attributes = sdlAttribs.data();
        pInfo.vertex_input_state.num_vertex_attributes = static_cast<uint32_t>(sdlAttribs.size());
        pInfo.vertex_input_state.vertex_buffer_descriptions = &buffDesc;
        pInfo.vertex_input_state.num_vertex_buffers = 1;
        pInfo.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;

        SDL_GPUColorTargetDescription colorDesc;
        SDL_zero(colorDesc);
        colorDesc.format = SDL_GetGPUSwapchainTextureFormat(m_Device, m_Window);
        pInfo.target_info.color_target_descriptions = &colorDesc;
        pInfo.target_info.num_color_targets = 1;

        SDL_GPUGraphicsPipeline* pipeline = SDL_CreateGPUGraphicsPipeline(m_Device, &pInfo);
        if(!pipeline){
            PE_LOG_ERROR("Renderer: failed to create pipeline! Error: {}", SDL_GetError());
            return nullptr;
        }

        m_PipelineCache[key] = pipeline;
        return pipeline;
    }

}