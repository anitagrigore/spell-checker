# Remember not to fuck up

To install google test:
 - `sudo apt install googletest`
 - `cd /usr/src/googletest`
 - `mkdir bin`
 - `cmake ..`
 - `make && make_install`

To use it: in the `CMakeLists.txt` file of the project, create a `tests` target:

```
enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(tests tests/trie_test.cpp)
target_link_libraries(tests GTest::GTest GTest::Main)
gtest_discover_tests(tests)
```

Then `cd bin && cmake .. && make` and voila!
