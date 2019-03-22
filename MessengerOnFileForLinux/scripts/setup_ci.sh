#!/bin/bash
#CMAKE INSTALLATION
wget -qO- "https://cmake.org/files/v3.14/cmake-3.14.0-Linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C /usr/local
apt-get install --yes ncurses-dev
apt-get install --yes libncurses5-dev 
apt-get install --yes libncursesw5-dev
apt-get install --yes valgrind
apt-get install --yes python-setuptools
apt-get install --yes clang
apt-get install --yes clang-tidy
apt-get install --yes libyaml-dev
apt-get install --yes python3-dev
apt-get install --yes python-dev
apt-get install --yes doxygen
apt-get install --yes graphviz
apt-get install --yes lcov
easy_install pip
pip install pyyaml
