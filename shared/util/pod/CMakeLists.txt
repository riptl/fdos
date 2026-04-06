target_sources(fd_util PRIVATE
  fd_pod.c
)

if(BUILD_TESTING)
  add_executable(test_pod test_pod.c)
  target_link_libraries(test_pod PRIVATE fd_util)
  add_test(NAME test_pod COMMAND test_pod)
endif()
