#include "Core/LayerStack.h"
#include "Core/Base.h"
#include <algorithm>

namespace Pumpkin{
    LayerStack::~LayerStack(){
        for(auto& layer : m_Layers){
            layer->OnDetach();
        }
    }

    void LayerStack::PushLayer(Scope<Layer> layer){
        layer->OnAttach();
        
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIdx, PE_MOVE_SCOPE(layer));
        m_LayerInsertIdx++;
    }

    void LayerStack::PushOverlay(Scope<Layer> overlay){
        overlay->OnAttach();
        
        m_Layers.emplace_back(PE_MOVE_SCOPE(overlay));
    }

    void LayerStack::PopLayer(Scope<Layer> layer){
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if(it != m_Layers.end()){
            layer->OnDetach();
            m_Layers.erase(it);
            m_LayerInsertIdx--;
        }
    }

    void LayerStack::PopOverlay(Scope<Layer> overlay){
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if(it != m_Layers.end()){
            overlay->OnDetach();
            m_Layers.erase(it);
        }
    }
}