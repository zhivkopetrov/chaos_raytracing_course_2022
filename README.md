# chaos_raytracing_course_2022
Chaos raytracing course 2022

Requirements:
- C++ compiler
- cmake

Build steps:
step into the 'build' folder
configure and build the project based on your compiler settings

Compiler specific setup:
configuration + build (alternatively use the compiler specific front end API)

1) g++
cmake .. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=/usr/bin/g++
cmake --build . -j

2) clang++
cmake .. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=/usr/bin/clang++
cmake --build . -j

3) MSVC
cmake .. -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022"
cmake --build . -j

4) MinGW - fail. MinGW does not contain <thread> implementation
cmake .. -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"
cmake --build . -j

Running executables on Linux:
./tasks/02.images_and_colors/shape/shape
./tasks/02.images_and_colors/crt/crt
./tasks/03.vectors/rays/rays

Running executables on Windows:
tasks/02.images_and_colors/shape/Debug/shape.exe
tasks/02.images_and_colors/crt/Debug/crt.exe
tasks/03.vectors/rays/Debug/rays.exe

Results:
Can be found in 'results' folder in the project root directory

Task TODOs:
1) crt
- Implment MULTIPLE_PRODUCERS_SINGLE_ASYNC_CONSUMER strategy


