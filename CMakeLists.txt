cmake_minimum_required(VERSION 3.19)
project(ComputerGraphics)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(ComputerGraphics "Esercizi/Temp.c")

target_link_libraries(ComputerGraphics ${OPENGL_LIBRARIES})
target_link_libraries(ComputerGraphics ${GLUT_LIBRARIES})
target_link_libraries(ComputerGraphics -lopengl32 -g -lfreeglut)