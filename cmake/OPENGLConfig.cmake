cmake_minimum_required(VERSION 3.0)

#Make an interface library for OpenGL

find_package(OpenGL REQUIRED)

add_library(OpenGL INTERFACE)

#both gl and glu:
#target_link_libraries(OpenGL INTERFACE ${OPENGL_LIBRARIES})

#just gl only:
target_link_libraries(OpenGL INTERFACE ${OPENGL_gl_LIBRARY})

#not all systems need the include?
if(OPENGL_INCLUDE_DIR)
	target_include_directories(OpenGL SYSTEM INTERFACE ${OPENGL_INCLUDE_DIR})
endif()

