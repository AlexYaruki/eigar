cmake_minimum_required(VERSION 3.10)
project(eigar)
set(CMAKE_C_STANDARD 11)

include(CTest)
enable_testing()

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

file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c")
message(STATUS "Test sources: ${TEST_SOURCES}")
foreach(TEST_FILE_PATH ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE_PATH} NAME_WE)
    message(STATUS "Test name: ${TEST_NAME}")
    add_executable(${TEST_NAME} "")
    target_include_directories(
        ${TEST_NAME}
            PUBLIC
                ${CMAKE_CURRENT_SOURCE_DIR}/include/shared
    )
    target_sources(
        ${TEST_NAME}
            PRIVATE
                ${TEST_FILE_PATH}
    )
    target_link_libraries(${TEST_NAME} ${PROJECT_NAME})
    add_test(
            NAME ${TEST_NAME}
            COMMAND ${TEST_NAME})
endforeach()
