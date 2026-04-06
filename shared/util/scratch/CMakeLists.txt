target_sources(fd_util PRIVATE
  fd_scratch.c
)

if(BUILD_TESTING)
  add_executable(test_scratch test_scratch.c)
  target_link_libraries(test_scratch PRIVATE fd_util)
  add_test(NAME test_scratch COMMAND test_scratch)
endif()
