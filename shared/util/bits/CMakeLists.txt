target_sources(fd_util PRIVATE
  fd_bits.c
)

add_executable(test_bits test_bits.c)
target_link_libraries(test_bits PRIVATE fd_util)
add_test(NAME test_bits COMMAND test_bits)

add_executable(test_bits_tg test_bits_tg.c)
target_link_libraries(test_bits_tg PRIVATE fd_util)
add_test(NAME test_bits_tg COMMAND test_bits_tg)

add_executable(test_float test_float.c)
target_link_libraries(test_float PRIVATE fd_util)
add_test(NAME test_float COMMAND test_float)

add_executable(test_hash test_hash.c)
target_link_libraries(test_hash PRIVATE fd_util)
add_test(NAME test_hash COMMAND test_hash)

add_executable(test_uwide test_uwide.c)
target_link_libraries(test_uwide PRIVATE fd_util)
add_test(NAME test_uwide COMMAND test_uwide)
