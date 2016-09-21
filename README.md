# NEStor

NEStor is a Nintendo Entertainment System (NES)/Famicom emulator written in C++11 and fully tested.
It is still a work in progress, but the 6502 emulator is starting to be interesting.

## How to build
This project uses CMake. Therefore, you simply need to run CMake and set the parameters as desired.
I personnaly use the latest version of Visual Studio for programming and it works great. I tested it
once on a Linux virtual machine and the makefile generated was compiling everything as it should.

One important settings is the GTEST_ROOT. It must point to a valid and *compiled* version of [Google Test](https://github.com/google/googletest).
Google Test also uses CMake, so it should be quite easy to compile. Please note that for Visual Studio, you
need to compile it as a static library (do *not* check BUILD_SHARED_LIBS) and you must force it to you shared
CRT (check gtest_force_shared_crt). You also need to take the compiled files and move them to a directory
named "lib", next to the "include" directory. Otherwise, CMake can't find the files.
In the future, I will probably include Google Test as a submodule, making it simpler to compile.

## Why NEStor?
The name NEStor is a reference to the acronym "NES" and a reference to [Nestor](https://en.wikipedia.org/wiki/Nestor_(mythology)), a character in the Greek mythology.
I am not very good at naming stuff, but "Nestor" sounds good both in French and in English. Also, his
description in the Greek mythology is quite noble. He was a old sage who survived the Trojan War and he was
respected for his advices. So, I guess he was cool.