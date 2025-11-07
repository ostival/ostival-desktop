# Ostival Desktop

![Build](https://github.com/ostival/ostival-desktop/actions/workflows/cmake-multi-platform.yml/badge.svg)
![License](https://img.shields.io/github/license/ostival/ostival-desktop)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
![Issues](https://img.shields.io/github/issues/ostival/ostival-desktop)
![Stars](https://img.shields.io/github/stars/ostival/ostival-desktop)

## Description
Our motivation to start this project is:

1. **Democratizing Hardware:** We believe chip design should be accessible to everyone. This project aims to break down the barriers of expensive, proprietary EDA tools by providing a free, open-source flow from Verilog to GDSII.
2. **Modernizing EDA:** We're bringing a modern touch to EDA with a tool that is not only powerful and efficient but also intuitive to use, moving forward from outdated design philosophies of the past.
3. **The Future is Open:** The future of hardware development is open. This project fosters a collaborative ecosystem where innovation flourishes through transparency and community-driven development, rather than through closed-source solutions.

Ostival is currently in development. Once it becomes stable, we'll release installable binaries for all desktop platforms. So, stay tuned!

## Features
- High-performance C++ core optimized for speed and scalability
- Security and privacy-preserving design
- Integrates with leading open-source synthesis tools (e.g., Icarus Verilog, Yosys, ABC)
- Scalable and modular design for handling large VLSI design flows

## Depedencies

- Qt 6.10.0
- CMake 3.16
- Icarus Verilog*

\* Ostival doesn't come with the pre-compiled binary of Icarus Verilog. The user can install it manually on their PC. We'll add all tools to the community server in the future, so you don't have to worry about installing and managing different tools, and you can focus solely on designing the awesome hardware.

## How to Build an Ostival Desktop Application?
Create a folder named **build** and cd to build

    mkdir build && cd build

Then run the commands to build the executable file given below:
### Windows
    cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.10.0/mingw_64/lib/cmake"

    make

    C:\Qt\6.10.0\mingw_64\bin\windeployqt.exe C:\Users\username\ostival-desktop\build\Ostival.exe

    ./Ostival.exe
### Linux
    cmake .. -DCMAKE_PREFIX_PATH="$HOME/Qt/6.10.0/gcc_64"

    make

    ./Ostival
### Mac
    cmake .. -DCMAKE_PREFIX_PATH="$HOME/Qt/6.10.0/macos"

    make

    ./Ostival

## How to compile documentation?

- Install LaTeX and compile the code to get the PDF documentation 

Or

- Copy the LaTeX files in Overleaf and compile to get the PDF documentation

***
**Happy Designing!**<br>
**Team Ostival**<br>
**hello@ostival.org**