cmake_minimum_required(VERSION 3.0.0)
project(PiHttp2Server VERSION 1.0.0)

SET(EXECUTABLE_BINARY_NAME "PiHttp2Server")
SET(APPLICATION_BINARY_NAME "PiHttp2Server_lib")

set(CMAKE_SYSTEM_PROCESSOR armv7l)
set(CMAKE_CROSS_COMPILING 1)
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O2")
set(LINK_FLAGS "-lssl -lcrypto -lboost_thread -lboost_system -lboost_filesystem -ldl -pthread")
set(CMAKE_AR arm-linux-gnueabihf-ar)
set(CMAKE_LINKER arm-linux-gnueabihf-ld)
set(CMAKE_NM arm-linux-gnueabihf-nm)
set(CMAKE_OBJCOPY arm-linux-gnueabihf-objcopy)
set(CMAKE_OBJDUMP arm-linux-gnueabihf-objdump)
set(CMAKE_STRIP arm-linux-gnueabihf-strip)
set(CMAKE_RANLIB arm-linux-gnueabihf-ranlib)

# including source code of the project
set(PROJECT_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_HOME_DIRECTORY}/src)
set(RASPBERRY_LIB_DIR "/root/raspberry/lib")
set(RASPBERRY_INCLUDE_DIR "/root/raspberry/include")

file(GLOB SOURCE_FILES_TOP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SOURCE_FILES_NESTED
    ${PROJECT_SOURCE_DIR}/Interface/*.cpp
)
set(SOURCE_FILES ${SOURCE_FILES_TOP} ${SOURCE_FILES_NESTED})

find_library(LIB_ASIO libnghttp2_asio.a
    HINTS "/root/raspberry/lib/"
)
find_library(LIB_HTTP2 libnghttp2.a
    HINTS "/root/raspberry/lib/"
)
find_library(LIB_PARSER libhttp-parser.a
    HINTS "/root/raspberry/lib/"
)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${RASPBERRY_INCLUDE_DIR}")

link_directories("${RASPBERRY_LIB_DIR}")

add_executable(Http2Server ${SOURCE_FILES})
target_link_libraries(Http2Server ${LIB_ASIO} ${LIB_HTTP2} ${LIB_PARSER} ${LINK_FLAGS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
