#ifndef PUMPKIN_ENGINE_RENDERER_H
#define PUMPKIN_ENGINE_RENDERER_H

#include <SDL3/SDL.h>
#include <functional>
#include <string>
#include <cstdint>
#include <unordered_map>
#include "Render/Mesh.h"
#include "Render/Material.h"
#include "Render/Shader.h"
#include "Render/VertexLayout.h"

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

        template<typename VertexType, typename IndexType, size_t VertexCount, size_t IndexCount>
        inline Mesh AllocateMesh(Shader* shader, const VertexType (&vertexArray)[VertexCount], const IndexType (&indexArray)[IndexCount]){
            uint32_t vertexDataSize = static_cast<uint32_t>(VertexCount * sizeof(VertexType));
            uint32_t indexDataSize = static_cast<uint32_t>(IndexCount * sizeof(IndexType));
            SDL_GPUIndexElementSize indexElementSize = (sizeof(IndexType) == 2) ? SDL_GPU_INDEXELEMENTSIZE_16BIT : SDL_GPU_INDEXELEMENTSIZE_32BIT;
            return AllocateMeshRaw(
                vertexArray,
                vertexDataSize,
                indexArray,
                indexDataSize,
                indexElementSize 
            );
        }

        Shader* CreateShader(const std::string& vertPath, const std::string& fragPath, const VertexLayout& layout);
        void DestroyShader(Shader* shader); 

        void DrawObject(const Mesh& mesh, const Material& mat);

    private:
        Mesh AllocateMeshRaw(
            const void* vertexData, uint32_t vertexDataSize,
            const void* indexData, uint32_t indexDataSize, SDL_GPUIndexElementSize indexElementSize
        );

        void UploadToBuffer(SDL_GPUBuffer* buffer, uint32_t offset, const void* data, uint32_t size);
        void EnsureBufferCapacity(SDL_GPUBuffer*& buffer, uint32_t& currentSize, uint32_t currentOffset, uint32_t newDataSize, SDL_GPUBufferUsageFlags usage);

        SDL_GPUShader* LoadShaderStage(const std::string& path, SDL_GPUShaderStage stage);
        SDL_GPUGraphicsPipeline* GetOrCreatePipeline(Shader* shader);

    private:
        struct PipelineKey{
            Shader* shader;

            bool operator==(const PipelineKey& other) const{
                return shader == other.shader; 
            }
        };
        struct PipelineKeyHash{
            std::size_t operator()(const PipelineKey& k) const{
                return std::hash<void*>()(k.shader);
            }
        };

        SDL_Window* m_Window = nullptr;
        SDL_GPUDevice* m_Device = nullptr;

        std::unordered_map<PipelineKey, SDL_GPUGraphicsPipeline*, PipelineKeyHash> m_PipelineCache;

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