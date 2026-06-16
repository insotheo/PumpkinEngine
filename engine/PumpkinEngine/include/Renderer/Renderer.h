#ifndef PUMPKIN_ENGINE_RENDERER_H
#define PUMPKIN_ENGINE_RENDERER_H

#include <SDL3/SDL.h>

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
    
    private:
        SDL_Window* m_Window = nullptr;
        SDL_GPUDevice* m_Device = nullptr;

        SDL_GPUCommandBuffer* m_CurrentCmd = nullptr;
        SDL_GPURenderPass* m_CurrentPass = nullptr;

        SDL_FColor m_ClearColor = {0.1f, 0.1f, 0.1f, 1.0f};

    };
}

#endif