cmake_minimum_required(VERSION 3.10)

project(scramble-visualizer VERSION 1.0)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(scramble-visualizer src/cube.cpp
                                   src/cube_face.cpp
                                   src/cube_graphic.cpp
                                   main.cpp)

target_include_directories(scramble-visualizer PUBLIC include)

target_compile_features(scramble-visualizer PRIVATE cxx_std_17)

target_compile_options(scramble-visualizer
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra>)

target_link_libraries(scramble-visualizer sfml-graphics)
