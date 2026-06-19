project(Sandbox)

file(GLOB SANDBOX_SOURCES
src/main.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})

target_link_libraries(Sandbox
PRIVATE PumpkinEngine
)


#FILES
file(GLOB TEST_DATA_FILES
testData/*.*
)

add_custom_command(
    TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${TEST_DATA_FILES}
        ${CMAKE_BINARY_DIR}/bin
    COMMENT "Copying test data files..."
)