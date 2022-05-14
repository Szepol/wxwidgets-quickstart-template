set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(
  SampleTest
  SampleTest.cc
)

target_link_libraries(
  SampleTest
  gtest
  gtest_main
  ui
)

add_test(SampleTests SampleTest)