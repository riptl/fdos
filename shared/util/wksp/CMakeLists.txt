target_sources(fd_util PRIVATE
  fd_wksp_admin.c
  fd_wksp_user.c
  fd_wksp_helper.c
  fd_wksp_free_treap.c
  fd_wksp_used_treap.c
)

add_executable(test_wksp test_wksp.c)
target_link_libraries(test_wksp PRIVATE fd_util)
add_test(NAME test_wksp COMMAND test_wksp)

add_executable(test_wksp_admin test_wksp_admin.c)
target_link_libraries(test_wksp_admin PRIVATE fd_util)
add_test(NAME test_wksp_admin COMMAND test_wksp_admin)

add_executable(test_wksp_free_treap test_wksp_free_treap.c)
target_link_libraries(test_wksp_free_treap PRIVATE fd_util)
add_test(NAME test_wksp_free_treap COMMAND test_wksp_free_treap)

add_executable(test_wksp_helper test_wksp_helper.c)
target_link_libraries(test_wksp_helper PRIVATE fd_util)
add_test(NAME test_wksp_helper COMMAND test_wksp_helper)

add_executable(test_wksp_used_treap test_wksp_used_treap.c)
target_link_libraries(test_wksp_used_treap PRIVATE fd_util)
add_test(NAME test_wksp_used_treap COMMAND test_wksp_used_treap)

add_executable(test_wksp_user test_wksp_user.c)
target_link_libraries(test_wksp_user PRIVATE fd_util)
add_test(NAME test_wksp_user COMMAND test_wksp_user)
