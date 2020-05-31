cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(gameproject1)

# Add source files.
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files.
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)


include_directories(
    /opt/vc/include
    /opt/vc/include/interface
    /opt/vc/include/interface/vcos/pthreads
    /opt/vc/include/interface/vmcs_host/linux
)

link_directories(
    /opt/vc/lib
)


set(RPi_LIBS
# Raspberry Pi - Broadcom
    libbcm_host.so
)

set(GL_LIBS
# openGLES
    GLESv2
    EGL
)

#define the executable.
add_executable(gameproject1 ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(gameproject1
        ${GL_LIBS}
	${RPi_LIBS}
)
