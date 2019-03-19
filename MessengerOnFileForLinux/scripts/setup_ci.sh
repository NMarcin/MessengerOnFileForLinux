#!/bin/bash
apt-get update --yes
wget http://www.cmake.org/files/v3.10/cmake-3.10.1.tar.gz
tar -xvzf cmake-3.10.1.tar.gz
cd cmake-3.10.1/
./configure
make 
make install
apt-get update
apt-get install --yes ncurses-dev
apt install --yes libncurses5-dev libncursesw5-dev
apt-get install --yes valgrind
apt-get update --yes
apt-get install --yes python-setuptools
easy_install pip
apt-get install --yes clang
apt-get install --yes clang-tidy
apt-get install --yes libyaml-dev
apt-get install --yes python3-dev
apt-get install --yes python-dev
pip install pyyaml
apt-get install --yes doxygen
apt-get install --yes graphviz
