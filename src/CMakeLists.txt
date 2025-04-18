### Project Sources ###
############################################################
set(APP_SOURCES
  # Base 
  ${APP_SRC_DIR}/app.cpp
  ${APP_SRC_DIR}/main.cpp
)
############################################################

### Library Sources ###
############################################################
set(LIBS_SOURCES 
  # STB
  ${APP_LIBS_DIR}/stb/stb_image.cpp
)
############################################################

### Final Build ###
############################################################
add_library(${APP_EXECUTABLE_NAME} ${APP_SOURCES})
############################################################

### Linking ###
############################################################
target_include_directories(${APP_EXECUTABLE_NAME} PUBLIC BEFORE ${APP_INCLUDES})
target_link_libraries(${APP_EXECUTABLE_NAME} PUBLIC ${APP_LIBRARIES})
############################################################

### Compiling Options ###
############################################################
target_compile_options(${APP_EXECUTABLE_NAME} PUBLIC ${APP_BUILD_FLAGS})
target_compile_features(${APP_EXECUTABLE_NAME} PUBLIC cxx_std_20)
############################################################
