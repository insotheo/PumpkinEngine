#ifndef PUMPKIN_ENGINE_BASE_H
#define PUMPKIN_ENGINE_BASE_H

#include <memory>

namespace Pumpkin{
    
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args){
        return std::make_shared<T>(std::forward<Args>(args)...);
    }


    template<typename T>
    using Ref = std::unique_ptr<T>;
    
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args){
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

}

#endif