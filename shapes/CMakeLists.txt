CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(shapes)

find_package(OpenGL)
find_package(GLUT)

include_directories( ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

add_executable(shapes shapes.c)

target_link_libraries(shapes ${OPENGL_gl_LIRABRY} ${GLUT_glut_LIBRARY} )
