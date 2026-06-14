#ifndef PUMPKIN_ENGINE_LAYER_STACK_H
#define PUMPKIN_ENGINE_LAYER_STACK_H

#include "Core/Layer.h"
#include "Core/Base.h"
#include <vector>

namespace Pumpkin{
    class LayerStack{
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Scope<Layer> layer);
        void PushOverlay(Scope<Layer> overlay);
        void PopLayer(Scope<Layer> layer);
        void PopOverlay(Scope<Layer> overlay);

        inline std::vector<Scope<Layer>>::iterator begin() { return m_Layers.begin(); } 
        inline std::vector<Scope<Layer>>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Scope<Layer>> m_Layers;
        unsigned int m_LayerInsertIdx = 0;
    };
}

#endif