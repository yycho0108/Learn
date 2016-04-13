cmake_minimum_required(VERSION 2.8)

project(HelloWorld)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(main main.cpp)

target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

