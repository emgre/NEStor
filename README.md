# NEStor
[![Build Status](https://travis-ci.org/emgre/NEStor.svg?branch=master)](https://travis-ci.org/emgre/NEStor)

NEStor is a Nintendo Entertainment System (NES)/Famicom emulator written in C++11 with extensive unit tests.
It is still a work in progress, but the 6502 emulator is starting to be interesting.

## How to build
This project uses CMake. Therefore, you simply need to run CMake and set the parameters as desired.
My main development platform is the latest version of Visual Studio on Windows 10. The master branch of this project
is also built with GCC 4.8.4 and Clang 3.5.0 automatically by [Travis CI](https://travis-ci.org/emgre/NEStor) and all
the unit tests are runned with both executables.

If you build it with the unit tests, please be sure to use the `--recursive` parameter when cloning the repository in order to download [Google Test](https://github.com/google/googletest). It will be compiled automatically by CMake and the tests will be available for CTest.

## Why NEStor?
The name NEStor is a reference to the acronym "NES" and a reference to [Nestor](https://en.wikipedia.org/wiki/Nestor_(mythology)), a character in the Greek mythology.
I am not very good at naming stuff, but "Nestor" sounds good both in French and in English. Also, his
description in the Greek mythology is quite noble. He was a old sage who survived the Trojan War and he was
respected for his advices. So, I guess he was cool.