cmake_minimum_required(VERSION 3.16)
project(F1TeamSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# All model classes are compiled into one library; the demo program links against it.
file(GLOB MODEL_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/model/*.cpp)
add_library(f1model ${MODEL_SOURCES})
target_include_directories(f1model PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(f1sim_demo src/main.cpp)
target_link_libraries(f1sim_demo PRIVATE f1model)
