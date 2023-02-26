cmake_minimum_required(VERSION 3.10)

project(StructuredExample
        VERSION 1.0
        DESCRIPTION "This is structured example project"
        LANGUAGES CXX
        )

add_executable(start main.cpp includes/print.hpp src/print.cppц)