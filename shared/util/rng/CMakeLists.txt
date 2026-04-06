target_sources(fd_util PRIVATE
  fd_rng.c
  fd_rng_secure.c
)

if(BUILD_TESTING)
  add_executable(test_rng test_rng.c)
  target_link_libraries(test_rng PRIVATE fd_util)
  add_test(NAME test_rng COMMAND test_rng)
endif()
