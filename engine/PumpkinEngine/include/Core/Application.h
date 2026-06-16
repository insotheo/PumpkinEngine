#ifndef PUMPKIN_ENGINE_APPLICATION_H
#define PUMPKIN_ENGINE_APPLICATION_H

#include "Core/Base.h"
#include "Core/Layer.h"
#include "Core/LayerStack.h"
#include "Core/Window.h"
#include "Renderer/Renderer.h"
#include <string>

namespace Pumpkin{
    struct ApplicationSpecification{
        std::string Name = "Pumpkin App";
        bool Headless = false;
    };

    class Application{
    public:
        explicit Application(const ApplicationSpecification& specification = ApplicationSpecification());
        virtual ~Application();

        void Run();
        inline void Stop() { m_Running = false; }
        
        inline static Application& Get() { return *s_AppInst; }

        inline void PushLayer(Scope<Layer> layer) { m_LayerStack.PushLayer(PE_MOVE_SCOPE(layer)); }
        inline void PushOverlay(Scope<Layer> overlay) { m_LayerStack.PushOverlay(PE_MOVE_SCOPE(overlay)); }

    private:
        static Application* s_AppInst;
        
        void OnEvent(Event& event);

        ApplicationSpecification m_AppSpecification;

        LayerStack m_LayerStack;
        Scope<Window> m_Window;
        Scope<Renderer> m_Renderer;

        bool m_Running;
    };

    Application* CreateApplication();

}

#endif