# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/net_lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/net_lib

# Include any dependencies generated for this target.
include CMakeFiles/net_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/net_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/net_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/net_lib.dir/flags.make

CMakeFiles/net_lib.dir/Src/Base/Date.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/Base/Date.cpp.o: Src/Base/Date.cpp
CMakeFiles/net_lib.dir/Src/Base/Date.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/net_lib.dir/Src/Base/Date.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/Base/Date.cpp.o -MF CMakeFiles/net_lib.dir/Src/Base/Date.cpp.o.d -o CMakeFiles/net_lib.dir/Src/Base/Date.cpp.o -c /root/net_lib/Src/Base/Date.cpp

CMakeFiles/net_lib.dir/Src/Base/Date.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/Base/Date.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/Base/Date.cpp > CMakeFiles/net_lib.dir/Src/Base/Date.cpp.i

CMakeFiles/net_lib.dir/Src/Base/Date.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/Base/Date.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/Base/Date.cpp -o CMakeFiles/net_lib.dir/Src/Base/Date.cpp.s

CMakeFiles/net_lib.dir/Src/Base/Logger.cc.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/Base/Logger.cc.o: Src/Base/Logger.cc
CMakeFiles/net_lib.dir/Src/Base/Logger.cc.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/net_lib.dir/Src/Base/Logger.cc.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/Base/Logger.cc.o -MF CMakeFiles/net_lib.dir/Src/Base/Logger.cc.o.d -o CMakeFiles/net_lib.dir/Src/Base/Logger.cc.o -c /root/net_lib/Src/Base/Logger.cc

CMakeFiles/net_lib.dir/Src/Base/Logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/Base/Logger.cc.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/Base/Logger.cc > CMakeFiles/net_lib.dir/Src/Base/Logger.cc.i

CMakeFiles/net_lib.dir/Src/Base/Logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/Base/Logger.cc.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/Base/Logger.cc -o CMakeFiles/net_lib.dir/Src/Base/Logger.cc.s

CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.o: Src/Base/Timestamp.cpp
CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.o -MF CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.o.d -o CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.o -c /root/net_lib/Src/Base/Timestamp.cpp

CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/Base/Timestamp.cpp > CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.i

CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/Base/Timestamp.cpp -o CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.s

CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.o: Src/net/InetAddress.cpp
CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.o -c /root/net_lib/Src/net/InetAddress.cpp

CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/InetAddress.cpp > CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.i

CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/InetAddress.cpp -o CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.s

CMakeFiles/net_lib.dir/Src/net/Socket.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/Socket.cpp.o: Src/net/Socket.cpp
CMakeFiles/net_lib.dir/Src/net/Socket.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/net_lib.dir/Src/net/Socket.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/Socket.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/Socket.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/Socket.cpp.o -c /root/net_lib/Src/net/Socket.cpp

CMakeFiles/net_lib.dir/Src/net/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/Socket.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/Socket.cpp > CMakeFiles/net_lib.dir/Src/net/Socket.cpp.i

CMakeFiles/net_lib.dir/Src/net/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/Socket.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/Socket.cpp -o CMakeFiles/net_lib.dir/Src/net/Socket.cpp.s

CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.o: Src/net/TCPServer.cpp
CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.o -c /root/net_lib/Src/net/TCPServer.cpp

CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/TCPServer.cpp > CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.i

CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/TCPServer.cpp -o CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.s

CMakeFiles/net_lib.dir/Src/net/Channel.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/Channel.cpp.o: Src/net/Channel.cpp
CMakeFiles/net_lib.dir/Src/net/Channel.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/net_lib.dir/Src/net/Channel.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/Channel.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/Channel.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/Channel.cpp.o -c /root/net_lib/Src/net/Channel.cpp

CMakeFiles/net_lib.dir/Src/net/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/Channel.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/Channel.cpp > CMakeFiles/net_lib.dir/Src/net/Channel.cpp.i

CMakeFiles/net_lib.dir/Src/net/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/Channel.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/Channel.cpp -o CMakeFiles/net_lib.dir/Src/net/Channel.cpp.s

CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.o: Src/net/EventLoop.cpp
CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.o -c /root/net_lib/Src/net/EventLoop.cpp

CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/EventLoop.cpp > CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.i

CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/EventLoop.cpp -o CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.s

CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.o: Src/net/Poller/Poller.cpp
CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.o -c /root/net_lib/Src/net/Poller/Poller.cpp

CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/Poller/Poller.cpp > CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.i

CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/Poller/Poller.cpp -o CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.s

CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.o: Src/net/DefaultPoller.cpp
CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.o -c /root/net_lib/Src/net/DefaultPoller.cpp

CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/DefaultPoller.cpp > CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.i

CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/DefaultPoller.cpp -o CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.s

CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.o: Src/net/Poller/EpollPoller.cpp
CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.o -c /root/net_lib/Src/net/Poller/EpollPoller.cpp

CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/Poller/EpollPoller.cpp > CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.i

CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/Poller/EpollPoller.cpp -o CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.s

CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.o: Src/net/CurrentThread.cpp
CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.o -c /root/net_lib/Src/net/CurrentThread.cpp

CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/CurrentThread.cpp > CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.i

CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/CurrentThread.cpp -o CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.s

CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.o: Src/Base/Thread.cpp
CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.o -MF CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.o.d -o CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.o -c /root/net_lib/Src/Base/Thread.cpp

CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/Base/Thread.cpp > CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.i

CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/Base/Thread.cpp -o CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.s

CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.o: Src/net/EventLoopThread.cpp
CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.o -c /root/net_lib/Src/net/EventLoopThread.cpp

CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/EventLoopThread.cpp > CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.i

CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/EventLoopThread.cpp -o CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.s

CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.o: Src/net/EventLoopThreadPool.cpp
CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.o -c /root/net_lib/Src/net/EventLoopThreadPool.cpp

CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/EventLoopThreadPool.cpp > CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.i

CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/EventLoopThreadPool.cpp -o CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.s

CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.o: Src/net/Acceptor.cpp
CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.o -c /root/net_lib/Src/net/Acceptor.cpp

CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/Acceptor.cpp > CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.i

CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/Acceptor.cpp -o CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.s

CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.o: Src/net/TCPConnection.cpp
CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.o -c /root/net_lib/Src/net/TCPConnection.cpp

CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/TCPConnection.cpp > CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.i

CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/TCPConnection.cpp -o CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.s

CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.o: Src/net/Buffer.cpp
CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.o -MF CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.o.d -o CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.o -c /root/net_lib/Src/net/Buffer.cpp

CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/net/Buffer.cpp > CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.i

CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/net/Buffer.cpp -o CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.s

CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.o: Src/memoryPool/memoryPool.cpp
CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.o -MF CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.o.d -o CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.o -c /root/net_lib/Src/memoryPool/memoryPool.cpp

CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/memoryPool/memoryPool.cpp > CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.i

CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/memoryPool/memoryPool.cpp -o CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.s

CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.o: Src/http/HttpResponse.cpp
CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Building CXX object CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.o -MF CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.o.d -o CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.o -c /root/net_lib/Src/http/HttpResponse.cpp

CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/http/HttpResponse.cpp > CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.i

CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/http/HttpResponse.cpp -o CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.s

CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.o: Src/http/HttpContext.cpp
CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_21) "Building CXX object CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.o -MF CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.o.d -o CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.o -c /root/net_lib/Src/http/HttpContext.cpp

CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/http/HttpContext.cpp > CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.i

CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/http/HttpContext.cpp -o CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.s

CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.o: CMakeFiles/net_lib.dir/flags.make
CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.o: Src/http/HttpServer.cpp
CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.o: CMakeFiles/net_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_22) "Building CXX object CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.o -MF CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.o.d -o CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.o -c /root/net_lib/Src/http/HttpServer.cpp

CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/net_lib/Src/http/HttpServer.cpp > CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.i

CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/net_lib/Src/http/HttpServer.cpp -o CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.s

# Object files for target net_lib
net_lib_OBJECTS = \
"CMakeFiles/net_lib.dir/Src/Base/Date.cpp.o" \
"CMakeFiles/net_lib.dir/Src/Base/Logger.cc.o" \
"CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/Socket.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/Channel.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.o" \
"CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.o" \
"CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.o" \
"CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.o" \
"CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.o" \
"CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.o" \
"CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.o"

# External object files for target net_lib
net_lib_EXTERNAL_OBJECTS =

bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/Base/Date.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/Base/Logger.cc.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/Base/Timestamp.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/InetAddress.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/Socket.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/TCPServer.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/Channel.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/EventLoop.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/Poller/Poller.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/DefaultPoller.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/Poller/EpollPoller.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/CurrentThread.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/Base/Thread.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/EventLoopThread.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/EventLoopThreadPool.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/Acceptor.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/TCPConnection.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/net/Buffer.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/memoryPool/memoryPool.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/http/HttpResponse.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/http/HttpContext.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/Src/http/HttpServer.cpp.o
bin/libnet_lib.so: CMakeFiles/net_lib.dir/build.make
bin/libnet_lib.so: CMakeFiles/net_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/net_lib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_23) "Linking CXX shared library bin/libnet_lib.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/net_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/net_lib.dir/build: bin/libnet_lib.so
.PHONY : CMakeFiles/net_lib.dir/build

CMakeFiles/net_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/net_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/net_lib.dir/clean

CMakeFiles/net_lib.dir/depend:
	cd /root/net_lib && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/net_lib /root/net_lib /root/net_lib /root/net_lib /root/net_lib/CMakeFiles/net_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/net_lib.dir/depend

