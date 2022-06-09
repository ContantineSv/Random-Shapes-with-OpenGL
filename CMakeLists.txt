cmake_minimum_required(VERSION 3.14)

project(Shapes)

find_package(OpenGL REQUIRED)

if(NOT ${OPENGL_FOUND})
    message("OPENGL not found")
endif()

include_directories(${OPENGL_INCLUDE_DIR})

add_subdirectory(glfw)


add_executable(${PROJECT_NAME} main.cpp shapes.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw ${OPENGL_LIBRARIES})