cmake_minimum_required(VERSION 3.0)

# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

project(tiny_webserver LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(CMAKE_CXX_STANDARD)

if(WIN32) 
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()

if(NOT MSVC)
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPETY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
        set_property(GLOBAL PROPETY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
    endif()
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/src/include/base
    ${PROJECT_SOURCE_DIR}/src/include/net
    ${PROJECT_SOURCE_DIR}/src/include/net/poller
    ${PROJECT_SOURCE_DIR}/src/include/http
    ${PROJECT_SOURCE_DIR}/src/include/timer
    ${PROJECT_SOURCE_DIR}/src/include/logger
    ${PROJECT_SOURCE_DIR}/src/include/memory
    ${PROJECT_SOURCE_DIR}/src/include/mysql
)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/base SRC_BASE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/net SRC_NET)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/net/poller SRC_POLLER)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/http SRC_HTTP)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/timer SRC_TIMER)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/logger SRC_LOG)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/memory SRC_MEMORY)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/mysql SRC_MYSQL)

add_library(tiny_webserver SHARED
            ${SRC_BASE}
            ${SRC_NET}
            ${SRC_POLLER}
            ${SRC_HTTP}
            ${SRC_TIMER}
            ${SRC_LOG}
            ${SRC_MEMORY}
            ${SRC_MYSQL}
)

target_link_libraries(tiny_webserver pthread)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION include/tiny_webserver
        FILES_MATCHING PATTERN "*.h")

add_subdirectory(example)

# add_subdirectory(src/http)
add_subdirectory(src/http/test)

add_subdirectory(src/logger/test)

# add_subdirectory(src/memory/test)

# add_subdirectory(src/mysql/test)