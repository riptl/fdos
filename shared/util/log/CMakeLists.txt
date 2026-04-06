target_sources(fd_util PRIVATE
  fd_log.c
  fd_backtrace.c
)

add_executable(test_log test_log.c)
target_link_libraries(test_log PRIVATE fd_util)
add_test(NAME test_log COMMAND test_log)
