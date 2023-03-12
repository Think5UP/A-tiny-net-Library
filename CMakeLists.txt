cmake_minimum_required(VERSION 3.22.3)
project(net_lib LANGUAGES C CXX)


set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

#set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -pthread -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated  -Werror -Wno-unused-function")

set(CMAKE_CXX_STANDARD 11)

set(LIB_SRC
        Src/Base/Date.cpp
        Src/Base/Logger.cc
        Src/Base/Timestamp.cpp
        Src/net/InetAddress.cpp Src/net/Socket.cpp Src/net/TCPServer.cpp
        Src/net/EventLoop.cpp Src/net/Channel.cpp
        Src/net/Poller/Poller.cpp Src/net/DefaultPoller.cpp Src/net/Poller/EpollPoller.cpp
        Src/net/CurrentThread.cpp Src/Base/Thread.cpp Src/net/EventLoopThread.cpp Src/net/EventLoopThreadPool.cpp Src/net/Acceptor.cpp Src/net/TCPConnection.cpp Src/net/Buffer.cpp)

add_library(net_lib SHARED ${LIB_SRC})


add_executable(test Src/test/Logger_test.cpp)
add_dependencies(test net_lib)
target_link_libraries(test net_lib)

add_executable(test_Inet Src/test/Inet_test.cpp)
add_dependencies(test_Inet net_lib)
target_link_libraries(test_Inet net_lib)


#add_executable(test Src/test/Timestamp_test.net)
#add_dependencies(net_lib )


#add_executable(net_lib main.net Src/include/nocopyable.h Src/include/copyable.h Src/include/Types.h Src/include/Timestamp.h Src/test/Timestamp_test.net Src/net/Timestamp.net Src/include/Date.h Src/net/Date.net Src/test/Date_test.net)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
