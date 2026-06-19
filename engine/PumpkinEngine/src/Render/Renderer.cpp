#include "Render/Renderer.h"

#include "Core/Log.h"
#include <cstdint>

namespace Pumpkin{
    VertexLayout Renderer::s_DefaultLayouts[2] = {  //indices at VertexLayoutType are strictly corresponding
        //2d
        {{
            {"Position", ShaderDataType::Float2},
            {"UV", ShaderDataType::Float2}
        }},

        //3d
        {{
            {"Position", ShaderDataType::Float3}, 
            {"TexCoord", ShaderDataType::Float2}
        }},
    };

    Renderer::~Renderer(){
        Shutdown();
    }

    bool Renderer::Initialize(Window* window){
        if(!window || !(window->GetNative())) return false;
        m_Window = window->GetNative();

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

        window->SetVSync(window->GetVSync());

        glEnable(GL_DEPTH_TEST);
        
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        AllocateNewBlock();

        return true;
    }

    void Renderer::Shutdown(){
        for(auto& block : m_BuffersBlocks){
            if(block.VBO != 0){
                glUnmapNamedBuffer(block.VBO);
                glUnmapNamedBuffer(block.EBO);
                glDeleteBuffers(1, &block.VBO);
                glDeleteBuffers(1, &block.EBO);
                glDeleteVertexArrays(2, block.VAOs);
            }
        }
        m_BuffersBlocks.clear();

        if(m_GlCtx){
            SDL_GL_DestroyContext(m_GlCtx);
            m_GlCtx = nullptr;
        }
        m_Window = nullptr;
    }

    Mesh Renderer::AllocateMeshRaw(
        const void* vertexData, uint32_t vertexDataSize, VertexLayoutType type,
        const void* indexData, uint32_t indexDataSize, uint32_t indexCount
    ){
        if(vertexDataSize > PE_BLOCK_VBO_SIZE || indexDataSize > PE_BLOCK_EBO_SIZE){
            PE_LOG_ERROR("Renderer: Mesh is too huge");
            return Mesh();
        }

        uint32_t activeBlockIdx = (uint32_t)m_BuffersBlocks.size() - 1;
        BufferBlock* activeBlock = &m_BuffersBlocks[activeBlockIdx];

        bool fitVBO = (activeBlock->OffsetVBO + vertexDataSize) <= activeBlock->CapacityVBO;
        bool fitEBO = (activeBlock->OffsetEBO + indexDataSize) <= activeBlock->CapacityEBO;

        if(!fitVBO || !fitEBO){
            AllocateNewBlock();
            activeBlockIdx++;
            activeBlock = &m_BuffersBlocks[activeBlockIdx];
        }

        uint32_t stride = s_DefaultLayouts[static_cast<size_t>(type)].GetStride();
        uint32_t indexUnitSize = static_cast<uint32_t>(indexDataSize / indexCount);

        Mesh mesh;
        mesh.BlockIndex = activeBlockIdx;
        mesh.Type = type;
        mesh.IndexCount = indexCount;
        mesh.IndexType = (indexUnitSize == 2) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
        mesh.BaseVertex = activeBlock->OffsetVBO / stride;
        mesh.FirstIndex = activeBlock->OffsetEBO / indexUnitSize;

        std::memcpy(activeBlock->VboPtr + activeBlock->OffsetVBO, vertexData, vertexDataSize);
        std::memcpy(activeBlock->EboPtr + activeBlock->OffsetEBO, indexData, indexDataSize);

        activeBlock->OffsetVBO += vertexDataSize;
        activeBlock->OffsetEBO += indexDataSize;

        return mesh;
    }

    void Renderer::AllocateNewBlock(){
        BufferBlock block;
        block.CapacityVBO = PE_BLOCK_VBO_SIZE;
        block.CapacityEBO = PE_BLOCK_EBO_SIZE;

        //creating buffers
        glCreateBuffers(1, &block.VBO);
        glCreateBuffers(1, &block.EBO);

        GLbitfield flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
        //mem allocating
        glNamedBufferStorage(block.VBO, block.CapacityVBO, nullptr, flags);
        glNamedBufferStorage(block.EBO, block.CapacityEBO, nullptr, flags);

        block.VboPtr = (uint8_t*)glMapNamedBufferRange(block.VBO, 0, block.CapacityVBO, flags);
        block.EboPtr = (uint8_t*)glMapNamedBufferRange(block.EBO, 0, block.CapacityEBO, flags);

        SetupStaticVAOs(2, s_DefaultLayouts, block.VAOs);//!!!

        for(int i = 0; i < 2; ++i){        
            glVertexArrayVertexBuffer(block.VAOs[i], 0, block.VBO, 0, s_DefaultLayouts[i].GetStride());
            glVertexArrayElementBuffer(block.VAOs[i], block.EBO);
        }

        m_BuffersBlocks.push_back(block);
    }

    void Renderer::SetupStaticVAOs(size_t amount, VertexLayout* layouts, uint32_t* vaos){//2D is 1st, 3D is 2nd - STRICT!!!
        for(size_t i = 0; i < amount; ++i){
            glCreateVertexArrays(1, &vaos[i]);

            for(auto& el : layouts[i].GetElements()){
                uint32_t loc = el.GetLocation();

                glEnableVertexArrayAttrib(vaos[i], loc);

                glVertexArrayAttribFormat(
                    vaos[i],
                    loc,
                    el.GetComponentCount(),
                    el.GetOpenGLType(),
                    GL_FALSE,
                    el.GetOffset()
                );

                glVertexArrayAttribBinding(vaos[i], loc, 0); 
            }
        }
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

        if(!shader || mesh.IndexCount == 0) return;

        glUseProgram(shader->GetProgramID());
        mat.Bind();

        uint32_t vao = m_BuffersBlocks[mesh.BlockIndex].VAOs[static_cast<size_t>(mesh.Type)];
        glBindVertexArray(vao);

        uint32_t indexSize = (mesh.IndexType == GL_UNSIGNED_SHORT) ? 2 : 4;
        void* byteOffset = (void*)(uintptr_t)(mesh.FirstIndex * indexSize);

        glDrawElementsBaseVertex(
        GL_TRIANGLES, 
        mesh.IndexCount, 
        mesh.IndexType, 
        byteOffset,        
        mesh.BaseVertex    
        );
    }
}