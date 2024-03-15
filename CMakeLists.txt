message("******************************************************")
message("**************  B  ***********************************")
message("************   /  \\ **********************************")
message("***********  A  ** D  ****** hi! THREAD POOL  ********")
message("************   \\  / **********************************")
message("**************  C  ***********************************")



cmake_minimum_required(VERSION 3.20.0)

project(ThreadPool_Cpp)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")   # make_unique


option(WITH_TEST "Compile with test" ON)

# add CThreadPool environment info
include(cmake/ThreadPool_Cpp-env-include.cmake)

#这个地方需要改进
# 对外头文件路径
set(INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/include/")
# 对内头文件路径
set(PROJECT_INCLUDE_DIR_INTERNAL "${CMAKE_CURRENT_LIST_DIR}/threadpool_cpp/")	

add_subdirectory(./threadpool_cpp)


if(WITH_TEST)
    message("ATTENTION! Compile with test")
    add_subdirectory(./test)
endif()


