project(PumpkinEngineCore VERSION 0.0.1 LANGUAGES CXX)

set(ENGINE_CORE
    src/test.cpp
)

add_library(PumpkinEngineCore STATIC ${ENGINE_CORE})

target_include_directories(PumpkinEngineCore
    PUBLIC include/
)
