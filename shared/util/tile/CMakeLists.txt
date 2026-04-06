target_sources(fd_util PRIVATE
  fd_tile.c
  fd_tile_threads.c
)

add_executable(test_cpuset test_cpuset.c)
target_link_libraries(test_cpuset PRIVATE fd_util)
add_test(NAME test_cpuset COMMAND test_cpuset)

add_executable(test_tile test_tile.c)
target_link_libraries(test_tile PRIVATE fd_util)
add_test(NAME test_tile COMMAND test_tile)
