#pragma once

#include <format>
#include <iostream>

#ifdef PE_DEBUG

// DEFAULT
#define PE_LOG_TRACE(...)                                                      \
  do {                                                                         \
    std::cout << "\e[0m[TRACE]: " << std::format(__VA_ARGS__) << "\e[0m\n";    \
  } while (0)

#define PE_LOG_INFO(...)                                                       \
  do {                                                                         \
    std::cout << "\e[0;32m[INFO]: " << std::format(__VA_ARGS__) << "\e[0m\n";  \
  } while (0)

#define PE_LOG_WARN(...)                                                       \
  do {                                                                         \
    std::cout << "\e[0;33m[WARN]: " << std::format(__VA_ARGS__) << "\e[0m\n";  \
  } while (0)

#define PE_LOG_ERROR(...)                                                      \
  do {                                                                         \
    std::cerr << "\e[0;31m[ERROR]: " << std::format(__VA_ARGS__) << "\e[0m\n"; \
  } while (0)

// CORE
#define PE_LOG_CORE_TRACE(...)                                                 \
  do {                                                                         \
    std::cout << "\e[0m[TRACE(CORE)]: " << std::format(__VA_ARGS__)            \
              << "\e[0m\n";                                                    \
  } while (0)
#define PE_LOG_CORE_INFO(...)                                                  \
  do {                                                                         \
    std::cout << "\e[1;32m[INFO(CORE)]: " << std::format(__VA_ARGS__)          \
              << "\e[0m\n";                                                    \
  } while (0)
#define PE_LOG_CORE_WARN(...)                                                  \
  do {                                                                         \
    std::cout << "\e[1;33m[WARN(CORE)]: " << std::format(__VA_ARGS__)          \
              << "\e[0m\n";                                                    \
  } while (0)
#define PE_LOG_CORE_ERROR(...)                                                 \
  do {                                                                         \
    std::cerr << "\e[1;31m[ERROR(CORE)]: " << std::format(__VA_ARGS__)         \
              << "\e[0m\n";                                                    \
  } while (0)

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
