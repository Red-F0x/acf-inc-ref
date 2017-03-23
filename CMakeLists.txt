#
# run cmake in build directory With command:
#   on Windows with MinGW: cmake -G "MinGW Makefile" ../ 
#

#
# minimum required CMake version
cmake_minimum_required ( VERSION 2.8.7 )

message ( STATUS "Work Directory [${CMAKE_SOURCE_DIR}]" )

#
# the name of the project
project ( cppreflection )

#
# option's block
#

#
# enable gcc coverage if needed
# info at:
# http://www.network-theory.co.uk/docs/gccintro/gccintro_81.html
# https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/Gcov.html
if ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
  option( ENABLE_COVERAGE "Enable Coverage Reporting in GCC" FALSE )

  if ( ENABLE_COVERAGE )
    # todo add -O0
    add_definitions ( -fprofile-arcs -ftest-coverage )
    set( LINKER_FLAGS "${LINKER_FLAGS} -fprofile-arcs -ftest-coverage" )
  endif ( ENABLE_COVERAGE )
endif ()

#
# Specifying header search paths
include_directories ( ${CMAKE_SOURCE_DIR}/include )

#
# Setting language standard
#

#
# enable a particular language standard
set ( CPP17_FLAG "-std=c++1z" )

#
# set up additional compiler-related settings
#add_definitions(-Wall -Wextra -Wconversion -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wcast-qual -Wunused -Woverloaded-virtual -pedantic ${CPP17_FLAG})
add_definitions ( -Wall ${CPP17_FLAG} )

#
#
#set ( LINKER_FLAGS "${LINKER_FLAGS} ${CPP17_FLAG}" )

#
# Adding build targets
#

#
# test's
#
add_subdirectory ( ${CMAKE_SOURCE_DIR}/test )

#
# documentation
#
add_subdirectory ( ${CMAKE_SOURCE_DIR}/doc )
