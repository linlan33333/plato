#!/bin/bash

set -e

# 创建bin目录
if [ ! -d "bin" ]; then
    mkdir bin
fi

# 创建build目录
if [ ! -d "build" ]; then
    mkdir build
fi

rm -rf `pwd`/build/*
cd `pwd`/build &&
    cmake .. &&
    make