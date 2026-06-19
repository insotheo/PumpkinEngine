#ifndef PUMPKIN_ENGINE_TEXTURE_H
#define PUMPKIN_ENGINE_TEXTURE_H

#include "Thirdparty/glad/gl.h"
#include <string>

namespace Pumpkin{
    class Texture{
    public:
        Texture(const std::string& path);
        ~Texture();

        inline GLuint64 GetHandle() const { return m_TextureHandle; }

    private:
        GLuint m_RendererID = 0;
        GLuint64 m_TextureHandle = 0;
    };
}

#endif