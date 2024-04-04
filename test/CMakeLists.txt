# Project name
project(tests)

# Sources for tests
set(TESTS_SRC test.c)
set(RAND_TESTS_SRC rand_test.c)

# Creating tests
add_executable(${PROJECT_NAME} ${TESTS_SRC})
add_executable(${PROJECT_NAME}_rand ${RAND_TESTS_SRC})

# Linking lib to tests
target_link_libraries(${PROJECT_NAME} quadratic_equation_lib)
target_link_libraries(${PROJECT_NAME}_rand quadratic_equation_lib)

# Adding tests
add_test(NAME Test1 COMMAND ${PROJECT_NAME} test1)
add_test(NAME Test2 COMMAND ${PROJECT_NAME} test2)
add_test(NAME Test3 COMMAND ${PROJECT_NAME} test3)
add_test(NAME Test4 COMMAND ${PROJECT_NAME} test4)
add_test(NAME Test5 COMMAND ${PROJECT_NAME} test5)
add_test(NAME Test6 COMMAND ${PROJECT_NAME} test6)
add_test(NAME Test7 COMMAND ${PROJECT_NAME} test7)
add_test(NAME Test8 COMMAND ${PROJECT_NAME} test8)
add_test(NAME Test9 COMMAND ${PROJECT_NAME} test9)
add_test(NAME Test10 COMMAND ${PROJECT_NAME} test10)
add_test(NAME Test11 COMMAND ${PROJECT_NAME} test11)
add_test(NAME Test12 COMMAND ${PROJECT_NAME} test12)
add_test(NAME Test13 COMMAND ${PROJECT_NAME} test13)
add_test(NAME Test14 COMMAND ${PROJECT_NAME} test14)
add_test(NAME Test15 COMMAND ${PROJECT_NAME} test15)

# Adding random tests
add_test(NAME Test16 COMMAND ${PROJECT_NAME}_rand)
