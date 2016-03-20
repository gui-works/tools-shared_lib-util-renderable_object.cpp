cmake_minimum_required(VERSION 3.2.2)

add_subdirectory(../shared_lib shared_lib)

# Boost
set(Boost_USE_STATIC_LIBS  ON)
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED system filesystem)
include_directories(${Boost_INCLUDE_DIRS})

# Point Cloud Library
find_package(PCL REQUIRED common kdtree search)
include_directories(${PCL_INCLUDE_DIRS})

# Eigen3
include_directories("/usr/local/include/eigen3")

add_executable(pointcloud_viewer pointcloud_viewer.cpp) 
target_link_libraries(pointcloud_viewer
                      shared_lib
                      ${Boost_SYSTEM_LIBRARY} 
                      ${Boost_FILESYSTEM_LIBRARY}
)
