cmake_minimum_required(VERSION 2.8.3)
project(test_ik)
add_compile_options(-std=c++11)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg trac_ik_lib)
find_package(Boost REQUIRED COMPONENTS date_time)
find_package(orocos_kdl REQUIRED)

## Declare a catkin package
catkin_package(
  CATKIN_DEPENDS
    trac_ik_lib
  DEPENDS
    Boost
    orocos_kdl)

## Build talker and listener
#include_directories(include ${catkin_INCLUDE_DIRS} /usr/include/eigen3 /opt/ros/melodic/include/trac_ik)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${orocos_kdl_INCLUDE_DIRS}
)

add_executable(tester src/test_ik_do_thing.cpp)
target_link_libraries(tester
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  ${orocos_kdl_LIBRARIES}
)