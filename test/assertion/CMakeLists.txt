#
# static assertion test's
#

#
# aggregate all project source files into a single variable
#
set ( SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp )

#
# create an executable binary
#
add_executable ( assertion-test ${SOURCE_FILES} )