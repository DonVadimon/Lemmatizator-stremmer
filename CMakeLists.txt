cmake_minimum_required(VERSION 3.16)
project(Lemmatizator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -std=c++17")

include(ExternalProject)
find_package(Git REQUIRED)

##
### Test definitions ###
##

configure_file(CMakeList.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)

##
### End test definition ###
##


add_executable(${PROJECT_NAME} main.cpp)

file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(Lemmatization STATIC ${sources})
target_include_directories(Lemmatization PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC Lemmatization)