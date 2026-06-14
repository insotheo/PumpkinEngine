#ifndef PUMPKIN_ENGINE_APPLICATION_H
#define PUMPKIN_ENGINE_APPLICATION_H

#include "Core/Base.h"
#include "Core/Layer.h"
#include "Core/LayerStack.h"

namespace Pumpkin{
    class Application{
    public:
        Application();
        virtual ~Application();

        void Run();
        inline void Stop() { m_Running = false; }
        
        inline static Application& Get() { return *s_AppInst; }

        inline void PushLayer(Scope<Layer> layer) { m_LayerStack.PushLayer(PE_MOVE_SCOPE(layer)); }
        inline void PushOverlay(Scope<Layer> overlay) { m_LayerStack.PushOverlay(PE_MOVE_SCOPE(overlay)); }

    private:
        static Application* s_AppInst;
        
        LayerStack m_LayerStack;

        bool m_Running;
    };

    Application* CreateApplication();

}

#endif