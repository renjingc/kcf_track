cmake_minimum_required(VERSION 2.8.3)
project(kcf_track)

if(NOT WIN32)
ADD_DEFINITIONS("-std=c++0x -O3")
endif(NOT WIN32)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
)

#set(CMAKE_PREFIX_PATH "/usr/local/opencv2/share/OpenCV")
find_package(OpenCV REQUIRED )

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES tcpclient
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

add_executable(KCF 
	${PROJECT_SOURCE_DIR}/src/runtracker.cpp 
	${PROJECT_SOURCE_DIR}/src/kcftracker.cpp 
	${PROJECT_SOURCE_DIR}/src/fhog.cpp
	${PROJECT_SOURCE_DIR}/src/selectobject.cpp)
target_link_libraries(KCF ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})	
