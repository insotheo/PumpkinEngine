#include "Renderer/Renderer.h"

#include "Core/Debug.h"
#include "Core/Log.h"

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

}