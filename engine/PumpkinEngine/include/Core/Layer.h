#ifndef PUMPKIN_ENGINE_LAYER_H
#define PUMPKIN_ENGINE_LAYER_H

#include "Event/Event.h"
#include <string>

namespace Pumpkin{
    class Layer{
    public:
        Layer(const std::string& dbgName = "Layer") : m_DbgName(dbgName)
        {}
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DbgName; }

    private:
        std::string m_DbgName;
    };
}

#endif