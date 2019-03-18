#!/bin/bash

cd ../build/
cmake ..
make
cd bin
./messenger_binary_UT
cd ..
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '*Test*' '/usr/include/*' '/usr/lib/*' '*googletest*' -o utCoverage.info
genhtml coverageWithoutUnnecessaryFiles.info --output-directory out
$1 out/index.html
