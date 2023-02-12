#!/usr/bin/env bash

######################################################################

cd build
make -j8
cd tests
clear
./tests
