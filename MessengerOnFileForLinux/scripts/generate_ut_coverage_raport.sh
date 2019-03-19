#!/bin/bash

cd ../build/
cmake ..
make
cd bin
./messenger_binary_UT
cd ..
lcov --quiet --capture --directory . --output-file coverage.info
lcov --quiet --remove coverage.info '*Test*' '/usr/include/*' '/usr/lib/*' '*googletest*' -o utCoverage.info
genhtml --quiet utCoverage.info --output-directory out
$1 out/index.html &
