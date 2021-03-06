cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

find_package(Qt4 REQUIRED)
# enable/disable some Qt features
set( QT_USE_QTGUI FALSE )
set( QT_USE_QTOPENGL FALSE )
set( QT_USE_QTXML FALSE )
set( QT_USE_QTNETWORK TRUE )
include(${QT_USE_FILE})

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

#set(hdrs src/PushHMIServer.hpp src/HMIResponseServer.hpp)
set(srcs src/C11_agent_st.cpp src/C11_TCPServer.cpp src/C11_structs.cpp src/C11_Agent_Node.cpp src/C11Main.cpp src/tinyxml2.cpp)
set(hdrs src/C11_PushServer.hpp src/C11_HMIResponseServer.hpp src/C11_UntilOperatorIntervention.hpp src/C11_TCPServer.h src/C11_structs.h src/C11_Agent_Node.h src/C11Main.h src/tinyxml2.h)

qt4_automoc(${srcs})
QT4_WRAP_CPP(qt_moc_srcs ${hdrs})

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})
rosbuild_add_executable(C11_Agent ${hdrs} ${srcs} ${qt_moc_srcs})
target_link_libraries(C11_Agent ${QT_LIBRARIES})
