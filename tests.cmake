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
