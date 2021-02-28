#!/bin/bash
git submodule update --init --recursive
BUILD_DIR=$PWD/build
if [ -d ${BUILD_DIR} ]; then
  pushd $BUILD_DIR
    make -j8
  popd
else
  mkdir -p $BUILD_DIR
  pushd $BUILD_DIR
    cmake ..
    make -j8
  popd
fi

