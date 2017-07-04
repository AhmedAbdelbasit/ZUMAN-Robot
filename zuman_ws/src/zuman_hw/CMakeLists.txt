cmake_minimum_required(VERSION 2.8.3)
project(zuman_hw)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  zuman_msgs
  #message_generation
)

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs#   zuman_msgs
# )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES zuman_hw
  CATKIN_DEPENDS roscpp std_msgs zuman_msgs
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

#####################################

add_executable(HW_Node src/HW_Node.cpp)
target_link_libraries(HW_Node ${catkin_LIBRARIES})
add_dependencies(HW_Node zuman_msgs_generate_messages_cpp)
