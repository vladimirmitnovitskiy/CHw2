add_library(graph graph.c)
add_library(min_heap min_heap.c)

add_executable(states states.c)

target_link_libraries(states PRIVATE graph)
target_link_libraries(states PRIVATE min_heap)