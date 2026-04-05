target_sources(fd_util PRIVATE
  fd_stat.c
)

if(FDOS_TESTS)
  add_executable(test_sqrt test_sqrt.c)
  target_link_libraries(test_sqrt PRIVATE fd_util)
  add_test(NAME test_sqrt COMMAND test_sqrt)

  add_executable(test_stat test_stat.c)
  target_link_libraries(test_stat PRIVATE fd_util)
  add_test(NAME test_stat COMMAND test_stat)
endif()
