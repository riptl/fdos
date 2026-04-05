target_sources(fd_util PRIVATE
  fd_io.c
)

if(FDOS_TESTS)
  add_executable(test_io test_io.c)
  target_link_libraries(test_io PRIVATE fd_util)
  add_test(NAME test_io COMMAND test_io)
endif()
