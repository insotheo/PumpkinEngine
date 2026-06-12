project(PumpkinEngine VERSION 0.0.1 LANGUAGES CXX C)

file(GLOB ENGINE_SOURCES
src/test.cpp
)

add_library(PumpkinEngine STATIC ${ENGINE_SOURCES})

target_include_directories(PumpkinEngine
PUBLIC include/
)