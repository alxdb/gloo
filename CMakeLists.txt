cmake_minimum_required(VERSION 2.6)
project(gloo)

find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} INTERFACE ${OPENGL_LIBRARIES})

