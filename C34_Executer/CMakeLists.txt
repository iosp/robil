cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)


rosbuild_find_ros_package(actionlib_msgs)
include(${actionlib_msgs_PACKAGE_PATH}/cmake/actionbuild.cmake)
genaction()

rosbuild_init()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

rosbuild_genmsg()
rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

#=============== INCLUDES ==================================
#include_directories (includes/BTExecuter)  
#include_directories (includes/SimpleTask)  
rosbuild_add_boost_directories()

#=============== LINKER ====================================
#link_directories (${PROJECT_SOURCE_DIR}/lib)

#------------------------ executer -------------------------
rosbuild_add_executable(executer 
	src/TaskProxyConnectionByActionLib.cpp
	src/executer.cpp
)
rosbuild_link_boost(executer thread system filesystem)
target_link_libraries (executer BTExecuter)

#-----

rosbuild_add_executable(stack_stream_filter 
	src/stack_stream_filter.cpp
)
rosbuild_link_boost(stack_stream_filter thread system filesystem regex)


#------------------------ test_action_client ---------------
#rosbuild_add_executable(test_action_client src/test_action_client.cpp)
#rosbuild_link_boost(test_action_client thread)


