#ifndef PUMPKIN_ENGINE_APPLICATION_H
#define PUMPKIN_ENGINE_APPLICATION_H

namespace Pumpkin{
    class Application{
    public:
        Application();
        virtual ~Application();

        void Run();
        
        inline static Application& Get() { return *s_AppInst; }
    private:
        static Application* s_AppInst;
        
        bool m_Running;
    };

    Application* CreateApplication();

}

#endif