#ifndef PUMPKIN_ENGINE_RENDERER_H
#define PUMPKIN_ENGINE_RENDERER_H

#include <SDL3/SDL.h>
#include "Render/glad/gl.h"
#include <cstdint>
#include "Render/Mesh.h"
#include "Render/Material.h"

#define PE_MIN_BUFFER_SIZE 8 * 1024 //8 Kb

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
            const IndexType (&indexArray)[IndexCount]
        )
        {
            return AllocateMeshRaw(
                vertexArray, static_cast<uint32_t>(VertexCount * sizeof(VertexType)),
                indexArray, static_cast<uint32_t>(IndexCount * sizeof(IndexType)), static_cast<uint32_t>(IndexCount)
            );
        }

        Shader* CreateShader(const std::string& vertPath, const std::string& fragPath, const VertexLayout& layout);

        void DrawObject(const Mesh& mesh, const Material& mat);

    private:
        Mesh AllocateMeshRaw(
            const void* vertexData, uint32_t vertexDataSize,
            const void* indexData, uint32_t indexDataSize, uint32_t indexCount
        );

        SDL_Window* m_Window = nullptr;
        SDL_GLContext m_GlCtx = nullptr;
    };
}

#endif