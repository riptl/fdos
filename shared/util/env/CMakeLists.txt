target_sources(fd_util PRIVATE
  fd_env.c
)

add_executable(test_env test_env.c)
target_link_libraries(test_env PRIVATE fd_util)
add_test(NAME test_env COMMAND test_env)
