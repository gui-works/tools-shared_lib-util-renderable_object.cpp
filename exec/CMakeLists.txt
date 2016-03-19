cmake_minimum_required(VERSION 3.2.2)

add_subdirectory(../shared_lib shared_lib)

add_executable(pointcloud_viewer pointcloud_viewer.cpp) 
target_link_libraries(pointcloud_viewer
                      shared_lib
)
