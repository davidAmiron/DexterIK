cmake_minimum_required(VERSION 2.8.3)
project(dexter)

add_compile_options(-std=c++11)


find_package(catkin REQUIRED roscpp std_msgs trac_ik_lib)
find_package(Boost REQUIRED COMPONENTS date_time)
find_package(orocos_kdl REQUIRED)


catkin_package(
  CATKIN_DEPENDS
    trac_ik_lib
  DEPENDS
    Boost
    orocos_kdl
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${orocos_kdl_INCLUDE_DIRS}
)

add_library(dexter_lib src/Dexter.cpp)

add_executable(test_dexter src/test_dexter.cpp)
#add_dependencies(test_dexter src/Dexter.h)
target_link_libraries(test_dexter dexter_lib)

add_executable(dexter_control src/dexter_control.cpp)
target_link_libraries(dexter_control
  dexter_lib
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  ${orocos_kdl_LIBRARIES}
)

add_executable(button_press src/button_press.cpp)
target_link_libraries(button_press ${catkin_LIBRARIES})

add_executable(demo src/demo.cpp)
target_link_libraries(demo ${catkin_LIBRARIES})

