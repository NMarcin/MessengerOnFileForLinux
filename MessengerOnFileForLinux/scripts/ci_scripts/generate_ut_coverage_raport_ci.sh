#!/bin/bash
lcov --capture --directory .. --output-file coverage.info
lcov --remove coverage.info '*Test*' '/usr/include/*' '/usr/lib/*' '/usr/local/*' '*googletest*' -o coverageWithoutUnnecessaryFiles.info
genhtml coverageWithoutUnnecessaryFiles.info --output-directory ../../out
mv ${PROJECT_DIR}/out/index.html ${PROJECT_DIR}/out/1_UtCoverageRaport.html

