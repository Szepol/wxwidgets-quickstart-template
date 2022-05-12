set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(
	NodeTest
	NodeTest.cc
)
target_link_libraries(
	NodeTest
	${GTEST_BOTH_LIBARIES}
	domain
)

gtest_discover_tests(NodeTest)