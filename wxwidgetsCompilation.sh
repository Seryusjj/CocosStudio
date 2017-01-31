#!/bin/bash
cd external/wxWidgets/
mkdir gtk-build
cd gtk-build
mkdir instalationresult
../configure --with-opengl --enable-unicode --enable-monolithic --prefix=./instalationresult
make -j4
make install


