#ifndef PUMPKIN_ENGINE_RENDERER_H
#define PUMPKIN_ENGINE_RENDERER_H

#include <SDL3/SDL.h>
#include "Render/glad/gl.h"
#include <cstdint>
#include "Render/Mesh.h"
#include "Render/Shader.h"
#include "Render/Material.h"
#include "Render/BufferBlock.h"
#include "Render/VertexLayout.h"
#include "Render/DefaultVertexLayouts.h"

#define PE_BLOCK_VBO_SIZE 16 * 1024 * 1024 //16 Mb
#define PE_BLOCK_EBO_SIZE 4 * 1024 * 1024 //4 Mb

namespace Pumpkin{
    class Renderer{
    public:
        Renderer() = default;
        ~Renderer();

        bool Initialize(SDL_Window* nativeWindow);
        void Shutdown();
        inline void SetClearColor(float r, float g, float b, float a = 1.0f) { glClearColor(r, g, b, a); }
        inline void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
        inline void Present() { SDL_GL_SwapWindow(m_Window); }

        template<typename VertexType, typename IndexType, size_t VertexCount, size_t IndexCount>
        inline Mesh AllocateMesh(
            const VertexType (&vertexArray)[VertexCount],
            const IndexType (&indexArray)[IndexCount],
            VertexLayoutType type
        )
        {
            return AllocateMeshRaw(
                vertexArray, static_cast<uint32_t>(VertexCount * sizeof(VertexType)), type,
                indexArray, static_cast<uint32_t>(IndexCount * sizeof(IndexType)), static_cast<uint32_t>(IndexCount)
            );
        }

        Shader* CreateShader(const std::string& vertPath, const std::string& fragPath);

        void DrawObject(const Mesh& mesh, const Material& mat);

    private:
        static VertexLayout s_DefaultLayouts[2];
        void SetupStaticVAOs(size_t amount, VertexLayout* layouts, uint32_t* vaos);    

        Mesh AllocateMeshRaw(
            const void* vertexData, uint32_t vertexDataSize, VertexLayoutType type,
            const void* indexData, uint32_t indexDataSize, uint32_t indexCount
        );

        SDL_Window* m_Window = nullptr;
        SDL_GLContext m_GlCtx = nullptr;

        std::vector<BufferBlock> m_BuffersBlocks;
        void AllocateNewBlock();
    };
}

#endif