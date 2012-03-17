CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(Sierpinski)

find_package(OpenGL)
find_package(GLUT)

include_directories( ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

add_executable(sierpinski Sierpinski3D-2.c)

target_link_libraries(sierpinski ${OPENGL_gl_LIRABRY} ${GLUT_glut_LIBRARY} )
