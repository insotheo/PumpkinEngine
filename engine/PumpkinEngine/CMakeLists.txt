project(PumpkinEngine VERSION 0.0.1 LANGUAGES CXX C)

file(GLOB ENGINE_SOURCES
src/test.cpp
)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

add_library(PumpkinEngine STATIC ${ENGINE_SOURCES})

target_include_directories(PumpkinEngine
PUBLIC include/
)

target_link_libraries(PumpkinEngine
PUBLIC SDL3::SDL3)