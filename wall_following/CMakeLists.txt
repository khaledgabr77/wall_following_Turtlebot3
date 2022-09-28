cmake_minimum_required(VERSION 3.0.2)
project(wall_following)


## Here go all the packages needed to COMPILE the messages of topic, services and actions.
## Its only geting its paths, and not really importing them to be used in the compilation.
## Its only for further functions in CMakeLists.txt to be able to find those packages.
## In package.xml you have to state them as build
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

## Generate topic messages in the 'msg' folder
## In this function will be placed all the topic messages files of this package ( in the msg folder ) to be compiled.
#add_message_files(
#  FILES
#  Age.msg
#)

## Here is where the packages needed for the topic messages compilation are imported.
generate_messages(
  DEPENDENCIES
  std_msgs
)

## State here all the packages that will be needed by someone that executes something from your package.
## All the packages stated here must be in the package.xml as exec_depend
catkin_package(
  CATKIN_DEPENDS roscpp std_msgs message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
add_executable(wall_following src/wall_following.cpp)
add_dependencies(wall_following ${publish_age_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(wall_following
   ${catkin_LIBRARIES}
 )
add_dependencies(wall_following wall_following_generate_messages_cpp)
