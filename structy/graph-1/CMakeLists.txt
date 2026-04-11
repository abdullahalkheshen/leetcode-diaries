cmake_minimum_required(VERSION 3.20)
project(graph_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(undirected_graph undirected_graph.cpp)
add_executable(graph            graph.cpp)
add_executable(graph_warmup     graph_warmup.cpp)