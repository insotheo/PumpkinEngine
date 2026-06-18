project(PumpkinEngine VERSION 0.0.1 LANGUAGES CXX C)

file(GLOB ENGINE_SOURCES
src/Core/*.cpp
src/Event/*.cpp
src/Render/*.cpp
src/Render/glad/gl.c
)

set(ENGINE_DEFINITIONS)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG main
)
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
)
FetchContent_MakeAvailable(SDL3)
FetchContent_MakeAvailable(glm)

if(WIN32)
    list(APPEND ENGINE_DEFINITIONS PE_WIN32)
endif()

add_library(PumpkinEngine STATIC ${ENGINE_SOURCES})

target_include_directories(PumpkinEngine
PUBLIC include/
)

target_link_libraries(PumpkinEngine
PUBLIC SDL3::SDL3 glm::glm)

target_compile_definitions(PumpkinEngine
PUBLIC ${ENGINE_DEFINITIONS} $<$<CONFIG:Debug>:PE_DEBUG> $<$<CONFIG:Release>:PE_RELEASE>
)