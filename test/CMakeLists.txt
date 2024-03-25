
include_directories(${INCLUDE_PATH})

link_directories("${CMAKE_CURRENT_LIST_DIR}/../build/threadpool_cpp")
set(TEST_LIST
    demo1
    demo2)

foreach(demo ${TEST_LIST})
    add_executable(${demo}
            ${demo}.cpp
            func.cpp)
endforeach()
target_include_directories(demo2 PUBLIC "${PROJECT_INCLUDE_DIR_INTERNAL}")
target_link_libraries(demo2 thpool)