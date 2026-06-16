#include "Render/Renderer.h"

#include "Core/Debug.h"
#include "Core/Log.h"
#include <fstream>
#include <vector>

namespace Pumpkin{
    
    SDL_GPUShader* Renderer::LoadShader(const std::string& path, SDL_GPUShaderStage stage){
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
        shaderInfo.num_samplers = 0;
        shaderInfo.num_storage_textures = 0;
        shaderInfo.num_storage_buffers = 0;
        shaderInfo.num_uniform_buffers = 0;

        return SDL_CreateGPUShader(m_Device, &shaderInfo);
    }

    Material Renderer::CreateMaterial(const std::string& vertPath, const std::string& fragPath, uint32_t vertexStride){
        Material mat;

        SDL_GPUShader* vertShader = LoadShader(vertPath, SDL_GPU_SHADERSTAGE_VERTEX);
        SDL_GPUShader* fragShader = LoadShader(fragPath, SDL_GPU_SHADERSTAGE_FRAGMENT);

        if(!vertShader || !fragShader){
            PE_ASSERT(false, "Failed to load shaders for material");
            return mat;
        }

        SDL_GPUVertexAttribute attribs[2];
        //float3 pos
        SDL_zero(attribs[0]);
        attribs[0].location = 0;
        attribs[0].buffer_slot = 0;
        attribs[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
        attribs[0].offset = 0;

        //float3 color
        SDL_zero(attribs[1]);
        attribs[1].location = 1;
        attribs[1].buffer_slot = 0;
        attribs[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
        attribs[1].offset = 3 * sizeof(float);


        SDL_GPUVertexBufferDescription bufferDesc;
        SDL_zero(bufferDesc);
        bufferDesc.slot = 0;
        bufferDesc.pitch = vertexStride;
        bufferDesc.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;

        SDL_GPUGraphicsPipelineCreateInfo pInfo;
        SDL_zero(pInfo);
        pInfo.vertex_shader = vertShader;
        pInfo.fragment_shader = fragShader;

        pInfo.vertex_input_state.vertex_attributes = attribs;
        pInfo.vertex_input_state.num_vertex_attributes = 2;
        pInfo.vertex_input_state.vertex_buffer_descriptions = &bufferDesc;
        pInfo.vertex_input_state.num_vertex_buffers = 1;

        pInfo.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;

        SDL_GPUColorTargetDescription colorDesc;
        SDL_zero(colorDesc);
        colorDesc.format = SDL_GetGPUSwapchainTextureFormat(m_Device, m_Window);
        
        pInfo.target_info.color_target_descriptions = &colorDesc;
        pInfo.target_info.num_color_targets = 1;

        mat.Pipeline = SDL_CreateGPUGraphicsPipeline(m_Device, &pInfo);

        SDL_ReleaseGPUShader(m_Device, vertShader);
        SDL_ReleaseGPUShader(m_Device, fragShader);

        if(!mat.Pipeline){
            PE_LOG_ERROR("Renderer: Pipeline creation failed. Error: {}", SDL_GetError());
        }

        return mat;
    }

    void Renderer::DestroyMaterial(Material& material){
        if(material.Pipeline){
            SDL_ReleaseGPUGraphicsPipeline(m_Device, material.Pipeline);
            material.Pipeline = nullptr;
        }
    }

}