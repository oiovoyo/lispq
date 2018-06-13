cmake_minimum_required (VERSION 2.8)
project(LISPQ)
file(GLOB SOURCES "*.c")
add_library(mpc ${SOURCES})
