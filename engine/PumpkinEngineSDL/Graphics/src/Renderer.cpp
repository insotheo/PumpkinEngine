#include "Renderer.hpp"

#include <Core/Log.hpp>

namespace Pumpkin::SDL::Graphics {

void Renderer::Init(SDL_Window *wnd) {
  m_Wnd = wnd;

  m_Device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV |
                                     SDL_GPU_SHADERFORMAT_DXIL |
                                     SDL_GPU_SHADERFORMAT_MSL,
#if PE_DEBUG
                                 true,
#else
                                 false,
#endif
                                 nullptr);

  if (!m_Device) {
    PE_LOG_CORE_ERROR("Failed to create GPU device: ", SDL_GetError());
    m_Device = nullptr;
    return;
  }

  if (!SDL_ClaimWindowForGPUDevice(m_Device, m_Wnd)) {
    PE_LOG_CORE_ERROR("Failed to claim window for gpu: {}", SDL_GetError());
    SDL_DestroyGPUDevice(m_Device);
    m_Device = nullptr;
    return;
  }
}

void Renderer::Shutdown() {
  if (!m_Device)
    return;

  SDL_WaitForGPUIdle(m_Device);
  if (m_Wnd)
    SDL_ReleaseWindowFromGPUDevice(m_Device, m_Wnd);
  SDL_DestroyGPUDevice(m_Device);

  m_Device = nullptr;
  m_Wnd = nullptr;
}

void Renderer::Render() {
  SDL_GPUCommandBuffer *cmdBuff = SDL_AcquireGPUCommandBuffer(m_Device);
  if (!cmdBuff)
    return;

  SDL_GPUTexture *swapchainTxt;
  bool success = SDL_AcquireGPUSwapchainTexture(cmdBuff, m_Wnd, &swapchainTxt,
                                                nullptr, nullptr);
  if (!swapchainTxt || !success) {

    SDL_CancelGPUCommandBuffer(cmdBuff);
    return;
  }

  // base clear color
  SDL_GPUColorTargetInfo colorTargetInfo{};
  colorTargetInfo.texture = swapchainTxt;
  colorTargetInfo.clear_color =
      SDL_FColor{226 / 255.f, 120 / 255.f, 38 / 255.f, 1.0f};
  colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
  colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

  SDL_GPURenderPass *renderPass =
      SDL_BeginGPURenderPass(cmdBuff, &colorTargetInfo, 1, nullptr);

  // TODO DRAW CALLS

  SDL_EndGPURenderPass(renderPass);

  SDL_SubmitGPUCommandBuffer(cmdBuff);
}

} // namespace Pumpkin::SDL::Graphics
