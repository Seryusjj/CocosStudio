#!/bin/bash
cd external/wxWidgets/
mkdir gtk-build
cd gtk-build
printf installdir
../configure --with-opengl --enable-unicode --prefix=/usr
make -j4
make install


