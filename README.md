kdevwindowviewer
================

Plugin for KDevelop 4 that allows you to embedded any window

To install plugin:

1. mkdir build
2. cd build
3. cmake -DCMAKE_INSTALL_PREFIX=`kde4-config --prefix` ..
3.1 For debug:  cmake -DCMAKE_INSTALL_PREFIX=`kde4-config --prefix` -DCMAKE_BUILD_TYPE=debugfull ..
4. make
5. sudo make install
6. kbuildsycoca4