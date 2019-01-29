status of all supported libs: 
libewf(20171104)  libfvde(20180108)  libvhdi(20180403)  libvmdk(20180403) libbde(20181124)

Build Instruction:(we also try to find python libs to build pymodule)
1. git clone https://github.com/sspring/libyal_cmake.git 
2. build libewf default,change project name of CMakeLists.txt at second line else: like `project(libfvde C)`  
3. generate repo with cmake
4. msbuild /p:Configuration=Release /p:Platform=Win32 libewf.sln (change Platform to x64 if you want a 64-bit lib) 

Contact me if any problem occurred: cracker.zhou@gmail.com
