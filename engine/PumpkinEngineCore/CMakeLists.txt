project(PumpkinEngineCore VERSION 0.0.1 LANGUAGES CXX)

set(ENGINE_CORE
    src/Application.cpp
    src/EventTypeCounter.cpp
)

add_library(PumpkinEngineCore STATIC ${ENGINE_CORE})

target_include_directories(PumpkinEngineCore
    PUBLIC include/
)

target_compile_definitions(PumpkinEngineCore
    PUBLIC $<$<CONFIG:Debug>:PE_DEBUG> $<$<CONFIG:Release>:PE_RELEASE>
)
