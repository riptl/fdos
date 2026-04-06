target_sources(fd_util PRIVATE
  fd_cstr.c
)

if(BUILD_TESTING)
  add_executable(test_cstr test_cstr.c)
  target_link_libraries(test_cstr PRIVATE fd_util)
  add_test(NAME test_cstr COMMAND test_cstr)
endif()
