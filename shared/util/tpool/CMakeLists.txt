target_sources(fd_util PRIVATE
  fd_tpool.c
)

if(FDOS_TESTS)
  add_executable(test_tpool test_tpool.c)
  target_link_libraries(test_tpool PRIVATE fd_util)
  add_test(NAME test_tpool COMMAND test_tpool)
endif()
