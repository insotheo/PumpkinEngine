#ifndef PUMPKIN_ENGINE_LOG_H
#define PUMPKIN_ENGINE_LOG_H

#include <iostream>
#include <string>
#include <format>

namespace Pumpkin{
    class Log{
    public:
        enum class Level{
            Trace,
            Info,
            Warn,
            Error
        };

        template<typename... Args>
        static void Print(Level level, std::format_string<Args...> formatString, Args&&... args){
            std::string msg = std::format(formatString, std::forward<Args>(args)...);

            switch (level) {
                case Level::Trace:
                    std::cout << "\033[0m[TRACE]: " << msg << "\033[0m\n";
                    break;
                
                case Level::Info:
                    std::cout << "\033[32m[INFO]: " << msg << "\033[0m\n";
                    break;

                case Level::Warn:
                    std::cout << "\033[33m[WARN]: " << msg << "\033[0m\n";
                    break;

                case Level::Error:
                    std::cerr << "\033[31m[ERROR]: " << msg << "\033[0m\n";
                    break;
            }
        }
    };
}

#ifdef PE_DEBUG
    #define PE_LOG_TRACE(...)   Pumpkin::Log::Print(::Pumpkin::Log::Level::Trace, __VA_ARGS__)
    #define PE_LOG_INFO(...)    Pumpkin::Log::Print(::Pumpkin::Log::Level::Info, __VA_ARGS__)
    #define PE_LOG_WARN(...)    Pumpkin::Log::Print(::Pumpkin::Log::Level::Warn, __VA_ARGS__)
    #define PE_LOG_ERROR(...)   Pumpkin::Log::Print(::Pumpkin::Log::Level::Error, __VA_ARGS__)
#else
    #define PE_LOG_TRACE(...)   
    #define PE_LOG_INFO(...)    
    #define PE_LOG_WARN(...)    
    #define PE_LOG_ERROR(...)   
#endif

#endif