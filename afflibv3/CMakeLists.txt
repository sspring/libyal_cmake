cmake_minimum_required(VERSION 3.9)
project(afflib)

SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
add_subdirectory(../zlib ${PROJECT_BINARY_DIR}/zlib.dir)
if( NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(OPENSSL_DIR "C:/OpenSSL")
link_directories("${OPENSSL_DIR}/lib")
include_directories("${OPENSSL_DIR}/include" "../zlib" "include/afflib" "include"
					"lzma443/C" "lzma443/C/7zip/Compress/LZMA_Alone")


set( LZMA_OBJS  
	lzma443/C/7zip/Compress/LZMA_Alone/LzmaBench.cpp 
	lzma443/C/7zip/Compress/LZMA_Alone/LzmaRam.cpp 
	lzma443/C/7zip/Compress/LZMA_Alone/LzmaRamDecode.c 
	lzma443/C/7zip/Compress/LZMA_C/LzmaDecode.c 
	lzma443/C/7zip/Compress/Branch/BranchX86.c 
	lzma443/C/7zip/Compress/LZMA/LZMADecoder.cpp 
	lzma443/C/7zip/Compress/LZMA/LZMAEncoder.cpp 
	lzma443/C/7zip/Compress/LZ/LZInWindow.cpp 
	lzma443/C/7zip/Compress/LZ/LZOutWindow.cpp 
	lzma443/C/7zip/Compress/RangeCoder/RangeCoderBit.cpp 
	lzma443/C/7zip/Common/InBuffer.cpp 
	lzma443/C/7zip/Common/OutBuffer.cpp 
	lzma443/C/7zip/Common/StreamUtils.cpp 
	lzma443/C/Common/Alloc.cpp 
	lzma443/C/Common/CommandLineParser.cpp 
	lzma443/C/Common/CRC.cpp 
	lzma443/C/Common/String.cpp 
	lzma443/C/Common/StringConvert.cpp 
	lzma443/C/Common/StringToInt.cpp 
	lzma443/C/Common/Vector.cpp 
	)

set(AFF_OBJS  
	lib/aff_db.cpp 
	lib/aff_toc.cpp 
	lib/afflib.cpp 
	lib/afflib_os.cpp 
	lib/afflib_pages.cpp 
	lib/afflib_stream.cpp 
	lib/afflib_util.cpp 
	lib/crypto.cpp 
	lib/base64.cpp
	lib/lzma_glue.cpp
	lib/s3_glue.cpp
	lib/vnode_aff.cpp
	lib/vnode_afd.cpp
	lib/vnode_afm.cpp
	lib/vnode_raw.cpp
	lib/vnode_s3.cpp
	lib/vnode_split_raw.cpp
	lib/utils.cpp
	lib/display.cpp
	)

add_library(afflib STATIC ${LZMA_OBJS} ${AFF_OBJS})
target_link_libraries(afflib ws2_32 advapi32 zlib libeay32)
target_compile_definitions(afflib PRIVATE -D_CRT_SECURE_NO_DEPRECATE -DHAVE_CONFIG_WINDOWS_H -DHAVE_LIBCRYPTO -DHAVE_OPENSSL_EVP_H -DHAVE_WINDOWS_API -DHAVE_MEMMOVE)
find_package(PythonLibs)
if(WIN32 AND PYTHONLIBS_FOUND)
	include_directories("${PYTHON_INCLUDE_DIRS}")
	add_library(pyaff SHARED pyaff/pyaff.c)
	set_target_properties(pyaff PROPERTIES SUFFIX ".pyd")
	target_link_libraries(pyaff afflib "${PYTHON_LIBRARIES}")
endif()