#ifndef PUMPKIN_ENGINE_APPLICATION_H
#define PUMPKIN_ENGINE_APPLICATION_H

namespace Pumpkin{
    class Application{
    public:
        Application();
        ~Application();

        void Run();
    
    private:
        bool m_Running;
    };
}

#endif