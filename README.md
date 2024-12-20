![visitors](https://visitor-badge.laobi.icu/badge?page_id=thejan14.adventofcode2024)

# Advent of Code 2024

Welcome to my [Advent of Code](https://adventofcode.com/2024) 2024 contribution! The solutions are written in C++23 using CMake, Ninja and the MSVC compiler on Windows. When writing the solutions code I primarily aim for readability but try to always keep performance considerations in mind (thought the latter strongly depends on how much time I can spend). Happy reading!

## What is Advent of Code?
Advent of code is made by [Eric Wastl](https://github.com/topaz).

> [It is] an Advent calendar of small programming puzzles for a variety of skill sets and skill levels that can be solved in any programming language you like. People use them as a speed contest, interview prep, company training, university coursework, practice problems, or to challenge each other.

For more information see [about Advent of Code](https://adventofcode.com/2024/about).

## Running the solutions
For running the code you need [Visual Studio 2022](https://visualstudio.microsoft.com/de/downloads/) with the [Desktop development with C++](https://learn.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=msvc-170) workload installed. Open the repository folder in Visual Studio and navigate to the "CMake Targets View" in the Solution explorer:

![grafik](https://github.com/thejan14/adventofcode2023/assets/7323693/49320c70-f2d1-45e0-bc46-f521e04c6167)

Right click the target you want to run and choose "Debug":

![Screenshot 2023-12-02 132742](https://github.com/thejan14/adventofcode2023/assets/7323693/e78ab986-b5ef-4298-82d4-9985355949a4)

You can also compile and run the code on Linux. Make sure you have the latest version of [CMake](https://cmake.org/) and [gcc](https://gcc.gnu.org/) installed (tested with CMake 3.27.7 and gcc 13.1.0). Note that gcc must be installed to `/usr/bin/gcc`. Then run the following command in the repository folder:
```
cmake -B./out/build --preset="x64-debug-linux" .
```

This will prepare your build files. To build the C++ code run:
```
cmake --build ".\out\build"
``` 

Now you can run the solutions by navigating to the respective build folder:
```
(cd ./out/build/dayXX/ && ./dayXXpartY)
```
