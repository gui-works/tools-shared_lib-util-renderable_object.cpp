cmake_minimum_required(VERSION 3.2.2)

project(mapping_tools)

SET(CMAKE_BUILD_TYPE Release)

# Check system
if(MSVC)
  add_definitions ("-DBOOST_ALL_NO_LIB -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -DNOMINMAX")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /bigobj /EHsc /fp:fast /wd4800 /wd4521 /wd4251 /wd4275 /wd4305 /wd4355 /wd4819 /wd4250 /wd4267")
  # no global code optimization to speed up compile
  #SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL /wd4800")
  #SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LTCG")
  #SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
  # /MANIFEST:NO") # please, don't disable manifest generation, otherwise crash at start for vs2008
else(MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth-1024 -stdlib=libc++")
endif()

set(OUTPUT_LIB_DIR ${PROJECT_BINARY_DIR}/lib)
set(OUTPUT_BIN_DIR ${PROJECT_BINARY_DIR}/bin)
make_directory(${OUTPUT_LIB_DIR})
make_directory(${OUTPUT_BIN_DIR})

if(WIN32)
  foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} CONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} "${OUTPUT_LIB_DIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} "${OUTPUT_BIN_DIR}")
    # ---[ Windows requires DLLs (shared libraries) to be installed in the same directory as executables
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG} "${OUTPUT_BIN_DIR}")
  endforeach(config)
else(WIN32)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_LIB_DIR}")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BIN_DIR}")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_LIB_DIR}")
endif(WIN32)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

################################################################################
####          3rd Party Header Only Libraries              #####################
################################################################################
include_directories(pkgs/glm)

################################################################################
####           SOURCE CODE                                 #####################
################################################################################
add_subdirectory(shared_lib)
add_subdirectory(exec)
