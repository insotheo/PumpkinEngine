#include "Render/Renderer.h"

#include "Core/Log.h"
#include "Render/Shader.h"
#include <cstdint>

namespace Pumpkin{
    Renderer::~Renderer(){
        Shutdown();
    }

    bool Renderer::Initialize(SDL_Window* nativeWindow){
        if(!nativeWindow) return false;
        m_Window = nativeWindow;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        m_GlCtx = SDL_GL_CreateContext(m_Window);
        if(!m_GlCtx){
            PE_LOG_ERROR("OpenGL: Failed to create context. Error: {}", SDL_GetError());
            return false;
        }

        if(!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)){
            PE_LOG_ERROR("OpenGL: Failed to initialize GLAD!");
            return false;
        }

        glEnable(GL_DEPTH_TEST);

        return true;
    }

    void Renderer::Shutdown(){
        if(m_GlCtx){
            SDL_GL_DestroyContext(m_GlCtx);
            m_GlCtx = nullptr;
        }
        m_Window = nullptr;
    }

    Mesh Renderer::AllocateMeshRaw(
        const void* vertexData, uint32_t vertexDataSize, const VertexLayout& layout,
        const void* indexData, uint32_t indexDataSize, uint32_t indexCount
    ){
        Mesh mesh;
        mesh.IndexCount = indexCount;

        glGenVertexArrays(1, &mesh.VAO);
        glGenBuffers(1, &mesh.VBO);
        glGenBuffers(1, &mesh.EBO);

        glBindVertexArray(mesh.VAO);

        //vertex
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);

        //index
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_STATIC_DRAW);

        for(const auto& el : layout.GetElements()){
            glEnableVertexAttribArray(el.GetLocation());
            glVertexAttribPointer(
                el.GetLocation(),
                el.GetComponentCount(),
                GL_FLOAT,
                GL_FALSE,
                layout.GetStride(),
                (void*)(uintptr_t)el.GetOffset()
            );
        }

        glBindVertexArray(0);
        return mesh;
    }

    Shader* Renderer::CreateShader(const std::string& vertPath, const std::string& fragPath){
        Shader* shader = new Shader();
        if(!shader->LoadFromFile(vertPath, fragPath)){
            delete shader;
            return nullptr;
        }
        return shader;
    }

    void Renderer::DrawObject(const Mesh& mesh, const Material& mat){
        Shader* shader = mat.GetShader();

        if(!shader || mesh.VAO == 0) return;

        glUseProgram(shader->ProgramID);

        glBindVertexArray(mesh.VAO);

        mat.ApplyUniforms();

        glDrawElements(GL_TRIANGLES, mesh.IndexCount, GL_UNSIGNED_SHORT, 0);

        glBindVertexArray(0);
        glUseProgram(0);
    }
}