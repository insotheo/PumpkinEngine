#ifndef PUMPKIN_ENGINE_RENDERER_H
#define PUMPKIN_ENGINE_RENDERER_H

#include <SDL3/SDL.h>
#include <string>
#include <cstdint>
#include "Render/RenderObject.h"
#include "Render/Material.h"

#define PE_MIN_BUFFER_SIZE 8 * 1024 //8 Kb

namespace Pumpkin{
    class Renderer{
    public:
        Renderer() = default;
        ~Renderer();

        bool Initialize(SDL_Window* nativeWindow);
        void Shutdown();
        inline void SetClearColor(float r, float g, float b, float a = 1.0f) { m_ClearColor = SDL_FColor{r, g, b, a}; }
        void Clear();
        void Present();

        RenderObject AllocateMesh(
            const void* vertexData, uint32_t vertexDataSize, uint32_t vertexStride,
            const void* indexData, uint32_t indexDataSize, SDL_GPUIndexElementSize indexElementSize
        );

        Material CreateMaterial(const std::string& vertPath, const std::string& fragPath, uint32_t vertexStride);
        void DestroyMaterial(Material& material);

        void DrawObject(const RenderObject& obj, const Material& mat);

    private:
        void UploadToBuffer(SDL_GPUBuffer* buffer, uint32_t offset, const void* data, uint32_t size);
        void EnsureBufferCapacity(SDL_GPUBuffer*& buffer, uint32_t& currentSize, uint32_t currentOffset, uint32_t newDataSize, SDL_GPUBufferUsageFlags usage);

        SDL_GPUShader* LoadShader(const std::string& path, SDL_GPUShaderStage stage);

    private:
        SDL_Window* m_Window = nullptr;
        SDL_GPUDevice* m_Device = nullptr;

        SDL_GPUCommandBuffer* m_CurrentCmd = nullptr;
        SDL_GPURenderPass* m_CurrentPass = nullptr;

        SDL_GPUBuffer* m_GlobVertexBuffer = nullptr;
        uint32_t m_CurrentVertexBufferSize = 0;
        uint32_t m_CurrentVertexOffsetBytes = 0;

        SDL_GPUBuffer* m_GlobIndexBuffer = nullptr;
        uint32_t m_CurrentIndexBufferSize = 0;
        uint32_t m_CurrentIndexOffsetBytes = 0;


        SDL_FColor m_ClearColor = {0.1f, 0.1f, 0.1f, 1.0f};

    };
}

#endif