#ifndef PUMPKIN_ENGINE_BASE_H
#define PUMPKIN_ENGINE_BASE_H

#include <memory>
#include <utility>

namespace Pumpkin{
    
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args){
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    #define PE_MOVE_SCOPE(scope) std::move(scope)

    
    template<typename T>
    using Ref = std::shared_ptr<T>;
    
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args){
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}

#endif