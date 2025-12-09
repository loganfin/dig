add_library(pit SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pit/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pit/window_impl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pit/event_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pit/state.cpp
)

target_include_directories(pit
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_compile_definitions(pit
    PRIVATE
        GLFW_INCLUDE_NONE
)

target_link_libraries(pit
    PRIVATE
        glfw
        glad_gl_core_4_6
)
