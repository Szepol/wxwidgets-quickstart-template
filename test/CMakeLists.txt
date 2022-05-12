set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(
    NodeTest
    NodeTest.cc
)

target_link_libraries(
    NodeTest
    gtest
    gtest_main
    domain
)

add_test(ReseauTests NodeTest)