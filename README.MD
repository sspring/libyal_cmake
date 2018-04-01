status of all supported libs: 
libewf(20171104).libfvde(20180108)
1. git clone https://github.com/sspring/libyal_cmake.git --recursive
2. generate repo with cmake
3. make ( make install is on the table), and you will find all libs are in bin\Release folder if using msvc or bin folder else.

Build libewf default,change project name of CMakeLists.txt at second line if necessary: 
like `project(libfvde C)` 
Contact me if any problem occurred: cracker.zhou@gmail.com