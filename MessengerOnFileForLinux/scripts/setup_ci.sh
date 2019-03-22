#!/bin/bash

#CMAKE INSTALLATION
wget -qO- "https://cmake.org/files/v3.14/cmake-3.14.0-Linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C /usr/local

#UBUNTU PACKAGES
apt-get update --yes
apt-get install --yes ncurses-dev\
                      libncurses5-dev\
                      libncursesw5-dev\
                      valgrind\
                      doxygen\
                      graphviz\
                      lcov\
                      clang\
                      clang-tidy
                      
#PYTHON PACKAGES NEEDED FOR CLANG-TIDY  
apt-get update --yes
apt-get install --yes python-setuptools
easy_install pip
apt-get install --yes libyaml-dev\
                      python3-dev\
                      python-dev\
pip install pyyaml

