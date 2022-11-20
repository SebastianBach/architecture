# Architecture Playground

Playground for some (C++) software architecture ideas.
More detailed documentation will be added in the future.

# Dependencies

- QT5 (https://www.qt.io/)
- Google Test (https://github.com/google/googletest); will be installed by CMake

# Build

Build with *CMake*:

```
mkdir build
cd build
cmake .. -DQt5_DIR=C:/my_qt_5_install/msvc2017_64/lib/cmake/Qt5 
cmake --build .
ctest

```
