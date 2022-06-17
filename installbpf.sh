#!/bin/bash

if ! [ -e /usr/local/bin/bpftrace ]
then
  sudo apt-get install -y libbpfcc-dev
  sudo apt-get update
  sudo apt-get install -y \
    bison \
    cmake \
    flex \
    g++ \
    git \
    libelf-dev \
    zlib1g-dev \
    libfl-dev \
    systemtap-sdt-dev \
    binutils-dev \
    libcereal-dev \
    llvm-12-dev \
    llvm-12-runtime \
    libclang-12-dev \
    clang-12 \
    libgtest-dev \
    libgmock-dev \
    asciidoctor
  git clone https://github.com/iovisor/bpftrace
  mkdir bpftrace/build; cd bpftrace/build;
  cmake -DCMAKE_BUILD_TYPE=Release ..
  make -j8
  sudo make install
fi