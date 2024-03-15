
include_directories(${INCLUDE_PATH})

link_directories("${CMAKE_CURRENT_LIST_DIR}/../build/threadpool_cpp")
set(TEST_LIST
    test)

foreach(test ${TEST_LIST})
    add_executable(${test}
            ${test}.cpp
            )
    target_include_directories(test PUBLIC "${PROJECT_INCLUDE_DIR_INTERNAL}")
    target_link_libraries(test thpool)
endforeach()