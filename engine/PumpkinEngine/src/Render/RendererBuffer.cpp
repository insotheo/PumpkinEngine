#include "Render/Renderer.h"

namespace Pumpkin{

    void Renderer::UploadToBuffer(SDL_GPUBuffer* buffer, uint32_t offset, const void* data, uint32_t size){
        SDL_GPUTransferBufferCreateInfo tInfo = {SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD, size};
        SDL_GPUTransferBuffer* transferBuff = SDL_CreateGPUTransferBuffer(m_Device, &tInfo);

        //copy from RAM to transfer buffer
        void* mapped = SDL_MapGPUTransferBuffer(m_Device, transferBuff, false);
        std::memcpy(mapped, data, size);
        SDL_UnmapGPUTransferBuffer(m_Device, transferBuff);

        //write command
        SDL_GPUCommandBuffer* cmd = SDL_AcquireGPUCommandBuffer(m_Device);
        SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(cmd);

        SDL_GPUTransferBufferLocation src = {transferBuff, 0};
        SDL_GPUBufferRegion dest = {buffer, offset, size};
        SDL_UploadToGPUBuffer(copyPass, &src, &dest, false);

        SDL_EndGPUCopyPass(copyPass);
        SDL_SubmitGPUCommandBuffer(cmd);

        SDL_ReleaseGPUTransferBuffer(m_Device, transferBuff);
    }

    void Renderer::EnsureBufferCapacity(SDL_GPUBuffer*& buffer, uint32_t& currentSize, uint32_t currentOffset, uint32_t newDataSize, SDL_GPUBufferUsageFlags usage){
        if(!buffer || (currentOffset + newDataSize) > currentSize){
            
            uint32_t newSize = currentSize == 0 ? PE_MIN_BUFFER_SIZE : currentSize * 2;
            while(newSize < (currentOffset + newDataSize)){
                newSize *= 2;
            }

            SDL_GPUBufferCreateInfo bInfo;
            SDL_zero(bInfo);
            bInfo.usage = usage;
            bInfo.size = newSize;
            SDL_GPUBuffer* newBuffer = SDL_CreateGPUBuffer(m_Device, &bInfo);

            if(buffer && currentOffset > 0){
                SDL_GPUCommandBuffer* cmd = SDL_AcquireGPUCommandBuffer(m_Device);
                SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(cmd);

                SDL_GPUBufferRegion srcRegion = {buffer, 0, currentOffset};
                SDL_GPUBufferRegion destRegion = {newBuffer, 0, currentOffset};

                SDL_UploadToGPUBuffer(copyPass, reinterpret_cast<SDL_GPUTransferBufferLocation*>(&srcRegion), &destRegion, true);

                SDL_EndGPUCopyPass(copyPass);
                SDL_SubmitGPUCommandBuffer(cmd);

                SDL_ReleaseGPUBuffer(m_Device, buffer);
            }

            buffer = newBuffer;
            currentSize = newSize;       
        }
    }

}