cmake_minimum_required(VERSION 3.27)
project(WxWidgetsExample)

### Project Variables ###
############################################################
set(APP_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(APP_INCLUDE_DIR ${APP_SRC_DIR})
set(APP_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set(APP_LIBRARIES)
set(APP_INCLUDES 
  ${APP_INCLUDE_DIR} 
  ${APP_LIBS_DIR} 
)

# Platform-specific flags
if(WIN32)
  set(APP_BUILD_FLAGS
    "/W3"
  )
elseif(LINUX) 
  set(NIKOLA_BUILD_FLAGS
    "-lm" 
    "-w"
  )
endif()

set(APP_EXECUTABLE_NAME "wxExample")
############################################################

### CMake Variables ###
############################################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
############################################################

### Sub Directories ###
############################################################
add_subdirectory(src)
############################################################
