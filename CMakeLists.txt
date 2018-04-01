cmake_minimum_required(VERSION 3.9)
project(libewf C)

string(TOLOWER "${PROJECT_NAME}" proj_name_lower)
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
add_subdirectory(zlib)
add_subdirectory(bzip2)

string(SUBSTRING "${PROJECT_NAME}" 3 -1 py_name) # remove first three letters --- lib
set(py_name "py${py_name}")   # preffix py 

if( NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(libyal_sublibs_define -DHAVE_WIDE_CHARACTER_TYPE -DHAVE_LOCAL_LIBCERROR 
                -DHAVE_LOCAL_LIBCTHREADS -DHAVE_LOCAL_LIBCDATA -DHAVE_LOCAL_LIBCLOCALE 
                -DHAVE_LOCAL_LIBCNOTIFY -DHAVE_LOCAL_LIBCSPLIT -DHAVE_LOCAL_LIBUNA 
                -DHAVE_LOCAL_LIBCFILE -DHAVE_LOCAL_LIBCPATH -DHAVE_LOCAL_LIBBFIO 
                -DHAVE_LOCAL_LIBFCACHE -DHAVE_LOCAL_LIBFDATA -DHAVE_LOCAL_LIBFGUID 
                -DHAVE_LOCAL_LIBFVALUE -DHAVE_LOCAL_LIBHMAC -DHAVE_LOCAL_LIBCAES)
set(third_part_definitions -DHAVE_ZLIB -DHAVE_ZLIB_COMPRESS2 -DHAVE_MULTI_THREAD_SUPPORT)

if(MSVC)
    add_definitions( -D_CRT_SECURE_NO_DEPRECATE -D_UNICODE -DUNICODE)
else()
    set(dir ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME} )
    execute_process (
    COMMAND bash -l -c "cd ${dir} && ./autogen.sh && ./configure"
    WORKING_DIRECTORY ${dir} )
    add_definitions( -DHAVE_CONFIG_H)
endif()

include_directories("${PROJECT_NAME}/include" "${PROJECT_NAME}/common" "zlib" "bzip2" "${PROJECT_NAME}")
file(GLOB lib_sources "${PROJECT_NAME}/${PROJECT_NAME}/*.c")
if(WIN32)
    add_library(${PROJECT_NAME} SHARED  ${lib_sources})
else()
    add_library(${PROJECT_NAME} STATIC  ${lib_sources})
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} zlib bz2)
set(libyal_sublibs   libcfile libcerror libcnotify  libclocale libuna libbfio libfguid libfvalue  libcaes libcdata  libcpath libcsplit libcthreads  libfcache libfdata libhmac )
if("${proj_name_lower}" STREQUAL "libfvde")
	list(APPEND libyal_sublibs libfplist)
	list(APPEND libyal_sublibs_define -DHAVE_LOCAL_LIBFPLIST)
endif()

foreach(sub_lib ${libyal_sublibs})
    include_directories("${PROJECT_NAME}/${sub_lib}")
    file(GLOB sublib_sources "${PROJECT_NAME}/${sub_lib}/*.c")
    add_library(${sub_lib} STATIC ${sublib_sources})
    target_link_libraries(${PROJECT_NAME} ${sub_lib})
    if(MSVC)
        target_compile_definitions(${sub_lib} PRIVATE ${third_part_definitions} ${libyal_sublibs_define} -D_CRT_SECURE_NO_WARNINGS)
    else()
        target_compile_definitions(${sub_lib} PRIVATE ${third_part_definitions} ${libyal_sublibs_define} )
    endif()
endforeach()

if(WIN32)
    target_compile_definitions(libhmac PRIVATE ${third_part_definitions} ${libyal_sublibs_define} -DHAVE_WINCRYPT)
    target_compile_definitions(libcaes PRIVATE ${third_part_definitions} ${libyal_sublibs_define} -DHAVE_WINCRYPT)
    target_compile_definitions(${PROJECT_NAME} PRIVATE  ${third_part_definitions} ${libyal_sublibs_define} -D_CRT_SECURE_NO_WARNINGS -DZLIB_DLL -DBZ_DLL -DHAVE_WINCRYPT -DDLL_EXPORT)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE  ${third_part_definitions} ${libyal_sublibs_define})
endif()

# build pyewf if necessary
find_package(PythonLibs)
if(EXISTS "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/${py_name}" AND WIN32 AND PYTHONLIBS_FOUND)
	include_directories("${PYTHON_INCLUDE_DIRS}" "${PROJECT_NAME}/${py_name}")
	file(GLOB sublib_sources "${PROJECT_NAME}/${py_name}/*.c")
    add_library(${py_name} SHARED ${sublib_sources})
	set_target_properties(${py_name} PROPERTIES SUFFIX ".pyd")
	target_compile_definitions(${py_name} PRIVATE ${third_part_definitions} ${libyal_sublibs_define})
	target_link_libraries(${py_name} ${libyal_sublibs} ${PROJECT_NAME} "${PYTHON_LIBRARIES}")
endif()

target_link_libraries(libhmac libcerror)
target_link_libraries(libuna libcerror)
target_link_libraries(libcaes libcerror)
target_link_libraries(libclocale libcerror)
target_link_libraries(libcnotify libcerror)
target_link_libraries(libcsplit libcerror)
target_link_libraries(libcthreads libcerror)
target_link_libraries(libfguid libcerror)
target_link_libraries(libcdata libcerror libcthreads)
target_link_libraries(libfcache libcerror libcdata  libcthreads)
target_link_libraries(libcfile libcerror libclocale libcnotify libuna)
target_link_libraries(libcpath libcerror libclocale libcsplit libuna)
target_link_libraries(libfdata libcerror libcdata libcnotify libcthreads libfcache)
target_link_libraries(libfvalue libcerror libcdata libcnotify libcthreads libfguid libuna)
target_link_libraries(libbfio libcerror libcdata libclocale libcnotify libcfile libcpath libcsplit libcthreads libuna)

list(FIND libyal_sublibs libfplist HAVE_LIBFPLIST)
if(NOT HAVE_LIBFPLIST EQUAL -1)
	target_link_libraries(libfplist libcerror libcdata libcnotify libfguid libfvalue libuna)
endif()