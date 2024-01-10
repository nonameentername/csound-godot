#!/bin/bash

. /emsdk/emsdk_env.sh

dir=$(realpath .)
src_dir=$dir/modules/csound
build_dir=$src_dir/build/web/debug
prefix=$dir/bin/web/debug

mkdir -p $build_dir
cd $build_dir

cmake -DCUSTOM_CMAKE=$src_dir/platform/wasm/Custom-wasm.cmake \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_VERBOSE_MAKEFILE=1 \
    -DCMAKE_INSTALL_PREFIX:PATH=$prefix \
    -DCMAKE_SYSTEM_NAME=Emscripten \
    -DUSE_VCPKG=1 \
    -DEMSDK=$EMSDK \
    -DEMSDK_NODE=$EMSDK_NODE \
    $src_dir

make
make install

cd $dir
scons platform=web target=template_debug dev_build=yes debug_symbols=yes
