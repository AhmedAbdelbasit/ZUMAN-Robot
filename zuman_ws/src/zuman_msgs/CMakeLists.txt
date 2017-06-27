cmake_minimum_required(VERSION 2.8.3)
project(zuman_msgs)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

add_message_files(
   FILES
   Qlandmark.msg
   Speeds.msg
   Odometry.msg
   Instruction.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS message_runtime roscpp std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(SubscriberNode src/SubscriberNode.cpp)
target_link_libraries(SubscriberNode ${catkin_LIBRARIES})
add_dependencies(SubscriberNode zuman_msgs_generate_messages_cpp)
