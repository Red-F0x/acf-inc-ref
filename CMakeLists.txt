#
# run cmake in build directory With command:
#   on Windows with MinGW: cmake -G "MinGW Makefile" ../ 
#

#
# minimum required CMake version
cmake_minimum_required ( VERSION 3.5.2 )

message (STATUS "work in '${CMAKE_SOURCE_DIR}' directory" )

#
# the name of the project
project ( acf-ref )

#
# Specifying header search paths
include_directories ( ${CMAKE_SOURCE_DIR}/include )

#
# aggregate all project source files into a single variable
set ( SOURCE_FILES ${CMAKE_SOURCE_DIR}/test/assertion/main.cpp )

#
# Setting language standard
#

#
# enable a particular language standard
# not works on CMake 3.5.2
#set ( CMAKE_CXX_STANDARD 1z )  # enable C++17 standard
set ( CPP17_FLAG "-std=c++1z" )

#
# set up additional compiler-related settings
#add_definitions(-Wall -Wextra -Wconversion -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wcast-qual -Wunused -Woverloaded-virtual  -pedantic ${CPP17_FLAG})
add_definitions ( -Wall ${CPP17_FLAG} )

#
#
#set ( LINKER_FLAGS "${LINKER_FLAGS} ${CPP17_FLAG}" )

#
# Adding build targets
#

#
# assertion test
#

#
# create an executable binary
add_executable ( acf-ref ${SOURCE_FILES} )

#
# documentation
#
add_subdirectory ( ${CMAKE_SOURCE_DIR}/doc )
