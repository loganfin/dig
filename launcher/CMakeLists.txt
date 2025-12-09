add_executable(launcher
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/file_watcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shared_library.cpp
)

target_include_directories(launcher
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(launcher
    PRIVATE
        pit
)

# These are pretty magic
target_compile_definitions(launcher
    PRIVATE
        LIB_DIG_BIN_PATH="${CMAKE_BINARY_DIR}/dig/libdig.so"
        LIB_DIG_SOURCE_PATH="${CMAKE_SOURCE_DIR}/dig"
)
