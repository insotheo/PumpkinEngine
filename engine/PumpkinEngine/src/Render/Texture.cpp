#define STB_IMAGE_IMPLEMENTATION
#define STBI_MAX_DIMENSIONS 4096 
#include "Thirdparty/stb/stb_image.h"

#include "Render/Texture.h"

#include "Core/Log.h"

namespace Pumpkin{
    Texture::Texture(const std::string& path){
        int width, height, channels;
        void* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
        if(!data){
            PE_LOG_ERROR("Texture: failed to load image: {}", path);
            return;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

        glTextureStorage2D(m_RendererID, 1, GL_RGBA8, width, height);
        glTextureSubImage2D(m_RendererID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        m_TextureHandle = glGetTextureHandleARB(m_RendererID);
        glMakeTextureHandleResidentARB(m_TextureHandle);

        stbi_image_free(data);
    }

    Texture::~Texture(){
        if(m_TextureHandle) glMakeTextureHandleNonResidentARB(m_TextureHandle);
        if(m_RendererID != 0) glDeleteTextures(1, &m_RendererID);
    }
}