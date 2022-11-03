#!/bin/bash
if [ ! -d "~/zenshot/build" ]; then
    mkdir -p ~/zenshot/build
fi
cd ~/zenshot/build
qmake ..
make -j8
cd -
