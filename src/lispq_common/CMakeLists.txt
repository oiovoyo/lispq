cmake_minimum_required (VERSION 2.8)
project(LISPQ)
file(GLOB SOURCES "*.c")
include_directories( "../mpc")
link_directories( "../mpc")
add_library(lispq_common ${SOURCES})
target_link_libraries(lispq_common mpc)
target_link_libraries(lispq_common edit)
