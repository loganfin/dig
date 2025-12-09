set(COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dig.cpp
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_executable(dig
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${COMMON_SOURCES}
    )
else()
    add_library(dig SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin.cpp
        ${COMMON_SOURCES}
    )
endif()

target_include_directories(dig
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(dig
    PRIVATE
        pit
)
