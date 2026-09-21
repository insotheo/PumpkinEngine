#pragma once

#include <format>
#include <iostream>

#ifdef PE_DEBUG

#define PE_LOG_TRACE(...)                                                      \
  std::cout << "\e[0m[TRACE]: " << std::format(__VA_ARGS__) << "\e[0m\n"
#define PE_LOG_INFO(...)                                                       \
  std::cout << "\e[0;32m[INFO]: " << std::format(__VA_ARGS__) << "\e[0m\n"
#define PE_LOG_WARN(...)                                                       \
  std::cout << "\e[0;33m[WARN]: " << std::format(__VA_ARGS__) << "\e[0m\n"
#define PE_LOG_ERROR(...)                                                      \
  std::cout << "\e[0;31m[ERROR]: " << std::format(__VA_ARGS__) << "\e[0m\n"

#define PE_LOG_CORE_TRACE(...)                                                 \
  std::cout << "\e[0m[TRACE(CORE)]: " << std::format(__VA_ARGS__) << "\e[0m\n"
#define PE_LOG_CORE_INFO(...)                                                  \
  std::cout << "\e[1;32m[INFO(CORE)]: " << std::format(__VA_ARGS__) << "\e[0m\n"
#define PE_LOG_CORE_WARN(...)                                                  \
  std::cout << "\e[1;33m[WARN(CORE)]: " << std::format(__VA_ARGS__) << "\e[0m\n"
#define PE_LOG_CORE_ERROR(...)                                                 \
  std::cout << "\e[1;31m[ERROR(CORE)]: " << std::format(__VA_ARGS__)           \
            << "\e[0m\n"
#else

#define PE_LOG_TRACE(...)
#define PE_LOG_INFO(...)
#define PE_LOG_WARN(...)
#define PE_LOG_ERROR(...)

#define PE_LOG_CORE_TRACE(...)
#define PE_LOG_CORE_INFO(...)
#define PE_LOG_CORE_WARN(...)
#define PE_LOG_CORE_ERROR(...)

#endif
