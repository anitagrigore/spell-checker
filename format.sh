#!/bin/sh

find . -name '*.cpp' -exec clang-format -verbose -i {} \;
find . -name '*.h' -exec clang-format -verbose -i {} \;
