cmake_minimum_required(VERSION 3.2.2)

project(mapping_tools)

# Find necessary packages
# OpenGL
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIR} )

# GLEW
find_package(GLEW REQUIRED)
include_directories($(GLEW_INCLUDE_DIRS))

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories( ${GLFW_INLUDE_DIRS} )
if(APPLE)
    option(GLFW_USE_RETINA "use retina" ON)
endif()

# ASSIMP for model loading
pkg_search_module(ASSIMP REQUIRED assimp)
include_directories( ${ASSIMP_INLUDE_DIRS} )

# Point Cloud Library
find_package(PCL REQUIRED common kdtree search io)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

set(EXTERNAL_LIBS
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    glfw3 ${GLFW_LIBRARIES}
    assimp ${ASSIMP_LIBRARIES}
    ${PCL_COMMON_LIBRARY} 
    ${PCL_KDTREE_LIBRARY}
    ${PCL_SEARCH_LIBRARY}
    ${PCL_IO_LIBRARY}
)

#################################################
#   Project Files
#################################################
file(GLOB core_source core/*.cpp core/*.cc)
file(GLOB core_header core/*.h)
file(GLOB util_source util/*.cpp)
file(GLOB util_header util/*.h)
file(GLOB exec_source exec/*.cpp)
set(srcs ${core_source}
         ${util_source}
         ${ui_source}
         ${exec_source})
set(incs ${core_header}
         ${util_header})

add_executable(pointcloud_viewer pointcloud_viewer.cpp)
target_link_libraries(pointcloud_viewer
                      ${EXTERNAL_LIBS} 
)
