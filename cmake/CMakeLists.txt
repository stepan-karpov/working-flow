cmake_minimum_required(VERSION 3.20)

project(StructuredExample
  VERSION 0.1
  DESCRIPTION "An example of structured project"
  LANGUAGES CXX
  )

# set(HEADERS_DIR "${StructuredExample_SOURCE_DIR}/include")
# set(SRC_DIR "${StructuredExample_SOURCE_DIR}/src")

set(HEADERS_DIR "${StructuredExample_SOURCE_DIR}/include")
set(SRC_DIR "${StructuredExample_SOURCE_DIR}/src")

message("Debug message!")
message("${HEADERS_DIR}")
message("${SRC_DIR}")

set(SOURCES
  main.cpp
  ${SRC_DIR}/print.cpp
)

# message("${SOURCE}")

add_executable(exec ${SOURCES})