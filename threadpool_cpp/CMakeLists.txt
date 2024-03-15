

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
# message("${SRC}")

include_directories(${PROJECT_INCLUDE_DIR_INTERNAL})

add_library(thpool SHARED ${SRC})

target_include_directories(thpool PUBLIC "${INCLUDE_PATH}")