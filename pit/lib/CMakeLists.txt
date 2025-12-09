# GLFW
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSALL OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)

# glad
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad/cmake)
glad_add_library(glad_gl_core_4_6 SHARED REPRODUCIBLE API gl:core=4.6)
