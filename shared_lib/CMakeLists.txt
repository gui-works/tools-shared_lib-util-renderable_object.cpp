cmake_minimum_required(VERSION 3.2.2)

# Find necessary packages
# OpenGL
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIR} )

# GLEW
find_package(GLEW REQUIRED)

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
if(APPLE)
    option(GLFW_USE_RETINA "use retina" ON)
endif()

# Eigen3
include_directories("/usr/local/include/eigen3")

# ASSIMP for model loading
#pkg_search_module(ASSIMP REQUIRED assimp)
#include_directories( ${ASSIMP_INLUDE_DIRS} )

# Point Cloud Library
#find_package(PCL REQUIRED common kdtree search io)
#include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})

set(EXTERNAL_LIBS
    ${OPENGL_LIBRARIES}
    glfw3 ${GLFW_LIBRARIES}
    ${GLEW_LIBRARIES}
    #assimp ${ASSIMP_LIBRARIES}
    #${PCL_COMMON_LIBRARY} 
    #${PCL_KDTREE_LIBRARY}
    #${PCL_SEARCH_LIBRARY}
    #${PCL_IO_LIBRARY}
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
         ${exec_source})
set(incs ${core_header}
         ${util_header})

include_directories(core util)

if(TARGET shared_lib)

message("shared_lib is already defined")

else()
add_library(shared_lib SHARED ${srcs} ${incs})
target_link_libraries(shared_lib
                      ${EXTERNAL_LIBS} 
)
target_include_directories(shared_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/util
)
endif()
