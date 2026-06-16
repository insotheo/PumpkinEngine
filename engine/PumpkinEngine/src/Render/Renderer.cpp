#include "Render/Renderer.h"

#include "Core/Debug.h"
#include "Core/Log.h"
#include "SDL3/SDL_gpu.h"
#include <cstdint>

namespace Pumpkin{
    Renderer::~Renderer(){
        Shutdown();
    }

    bool Renderer::Initialize(SDL_Window* nativeWindow){
        if(!nativeWindow) return false;
        m_Window = nativeWindow;

        //SHADERS FORMATS
        SDL_GPUShaderFormat formats = SDL_GPU_SHADERFORMAT_SPIRV;

#ifdef PE_DEBUG
        m_Device = SDL_CreateGPUDevice(formats, true, nullptr);
#else
        m_Device = SDL_CreateGPUDevice(formats, false, nullptr);
#endif

        if(!m_Device){
            PE_LOG_ERROR("Renderer: failed to create device. Error: {}", SDL_GetError());
            PE_ASSERT(false, "Device creation failed");

            return false;
        }

        if(!SDL_ClaimWindowForGPUDevice(m_Device, m_Window)){
            PE_LOG_ERROR("Renderer: Failed to claim window. Error: {}", SDL_GetError());
            PE_ASSERT(false, "Window claiming failed");
            
            SDL_DestroyGPUDevice(m_Device);
            m_Device = nullptr;

            return false;
        }

        return true;
    }

    void Renderer::Shutdown(){
        if(m_Device){
            if(m_GlobVertexBuffer){
                SDL_ReleaseGPUBuffer(m_Device, m_GlobVertexBuffer);
                m_GlobVertexBuffer = nullptr;
            }
            if(m_GlobIndexBuffer){
                SDL_ReleaseGPUBuffer(m_Device, m_GlobIndexBuffer);
                m_GlobIndexBuffer = nullptr;
            }
            if(m_CurrentPass){
                SDL_EndGPURenderPass(m_CurrentPass);
                m_CurrentPass = nullptr;
            }
            if(m_CurrentCmd){
                SDL_CancelGPUCommandBuffer(m_CurrentCmd);
                m_CurrentCmd = nullptr;
            }

            SDL_ReleaseWindowFromGPUDevice(m_Device, m_Window);
            SDL_DestroyGPUDevice(m_Device);
            m_Device = nullptr;
        }
        m_Window = nullptr;
    }

    void Renderer::Clear(){
        m_CurrentCmd = SDL_AcquireGPUCommandBuffer(m_Device);
        if(!m_CurrentCmd) return;

        SDL_GPUTexture* swapchainTexture = nullptr;
        uint32_t w, h;
        if(!SDL_AcquireGPUSwapchainTexture(m_CurrentCmd, m_Window, &swapchainTexture, &w, &h)){
            SDL_CancelGPUCommandBuffer(m_CurrentCmd);
            m_CurrentCmd = nullptr;
            return;
        }

        if(swapchainTexture){
            SDL_GPUColorTargetInfo colorTarget;
            SDL_zero(colorTarget);
            colorTarget.texture = swapchainTexture;
            colorTarget.clear_color = m_ClearColor;
            colorTarget.load_op = SDL_GPU_LOADOP_CLEAR;
            colorTarget.store_op = SDL_GPU_STOREOP_STORE;

            m_CurrentPass = SDL_BeginGPURenderPass(m_CurrentCmd, &colorTarget, 1, nullptr);
        }
    }

    void Renderer::Present(){
        if(m_CurrentPass){
            SDL_EndGPURenderPass(m_CurrentPass);
            m_CurrentPass = nullptr;
        }

        if(m_CurrentCmd){
            SDL_SubmitGPUCommandBuffer(m_CurrentCmd);
            m_CurrentCmd = nullptr;
        }
    }

    RenderObject Renderer::AllocateMesh(
        const void* vertexData, uint32_t vertexDataSize, uint32_t vertexStride,
        const void* indexData, uint32_t indexDataSize, SDL_GPUIndexElementSize indexElementSize
    ){
        EnsureBufferCapacity(m_GlobVertexBuffer, m_CurrentVertexBufferSize, m_CurrentVertexOffsetBytes, vertexDataSize, SDL_GPU_BUFFERUSAGE_VERTEX);
        EnsureBufferCapacity(m_GlobIndexBuffer, m_CurrentIndexBufferSize, m_CurrentIndexOffsetBytes, indexDataSize, SDL_GPU_BUFFERUSAGE_INDEX);

        RenderObject object;
        object.VertexStride = vertexStride;
        object.VertexOffsetBytes = m_CurrentVertexOffsetBytes;
        object.IndexOffsetBytes = m_CurrentIndexOffsetBytes;
        object.IndexElementSize = indexElementSize;

        uint32_t indexValSize = (indexElementSize == SDL_GPU_INDEXELEMENTSIZE_16BIT) ? 2 : 4;
        object.IndexCount = indexDataSize / indexValSize;

        UploadToBuffer(m_GlobVertexBuffer, m_CurrentVertexOffsetBytes, vertexData, vertexDataSize);
        UploadToBuffer(m_GlobIndexBuffer, m_CurrentIndexOffsetBytes, indexData, indexDataSize);

        //aligment for 16 bytes
        m_CurrentVertexOffsetBytes += (vertexDataSize + 15) & ~15;
        m_CurrentIndexOffsetBytes += (indexDataSize + 15) & ~15;

        return object;
    }

    void Renderer::DrawObject(const RenderObject& obj, const Material& mat){
        if(!m_CurrentPass || !mat.Pipeline) return;

        SDL_BindGPUGraphicsPipeline(m_CurrentPass, mat.Pipeline);

        SDL_GPUBufferBinding vertexBind = {m_GlobVertexBuffer, obj.VertexOffsetBytes};
        SDL_BindGPUVertexBuffers(m_CurrentPass, 0, &vertexBind, 1);

        SDL_GPUBufferBinding indexBind = {m_GlobIndexBuffer, obj.IndexOffsetBytes};
        SDL_BindGPUIndexBuffer(m_CurrentPass, &indexBind, obj.IndexElementSize);

        SDL_DrawGPUIndexedPrimitives(
            m_CurrentPass,
            obj.IndexCount,
            1,
            0,
            0,
            0
        );
    }
}