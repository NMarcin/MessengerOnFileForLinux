#!/bin/bash
cd /builds/NMarcin/MessengerOnFileForLinux/MessengerOnFileForLinux/
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make
