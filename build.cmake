file(GLOB_RECURSE SHARED_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/shared/*.h")
message(STATUS "Shared headers: ${SHARED_HEADERS}")
if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Linux")
    message(STATUS "Path: ${CMAKE_CURRENT_SOURCE_DIR}/src/os/linux")
    file(GLOB_RECURSE OS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/os/linux/*.c")
endif()
message(STATUS "OS sources: ${OS_SOURCES}")

add_library(${PROJECT_NAME} SHARED "")
target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include/shared
)
target_sources(${PROJECT_NAME}
        PRIVATE
            ${OS_SOURCES}
        )
