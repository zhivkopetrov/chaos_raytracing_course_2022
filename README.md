# chaos_raytracing_course_2022
Chaos raytracing course 2022

Build steps:
step into the 'build' folder
configure and build the project based on your compiler settings

Compiler specific setup:
configuration + build (alternatively use the compiler specific front end API)

g++
cmake .. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=/usr/bin/g++
cmake --build . -j

clang++
cmake .. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=/usr/bin/clang++
cmake --build . -j

MSVC
cmake .. -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 16 2019"
cmake --build . -j

MinGW - fail. MinGW does not contain <thread> implementation
cmake .. -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"
cmake --build . -j

Running executables:
./tasks/02.images_and_colors/shape/shape
./tasks/02.images_and_colors/crt/crt

Results:
Can be found in 'results' folder in the project root directory

General TODOs:
- Improve logging
- Read configs from a file

Task TODOs:
1) crt
- Implment MULTIPLE_PRODUCERS_SINGLE_ASYNC_CONSUMER strategy


