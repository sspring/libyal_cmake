if (bzip2_CONFIG_INCLUDED)
  return()
endif()
set(bzip2_CONFIG_INCLUDED TRUE)

set(bzip2_INCLUDE_DIRS C:/Program Files (x86)/libfvde/include)

foreach(lib bz2)
  set(onelib "${lib}-NOTFOUND")
  find_library(onelib ${lib}
    PATHS C:/Program Files (x86)/libfvde/lib
    NO_DEFAULT_PATH
    )
  if(NOT onelib)
    message(FATAL_ERROR "Library '${lib}' in package bzip2 is not installed properly")
  endif()
  list(APPEND bzip2_LIBRARIES ${onelib})
endforeach()

foreach(dep )
  if(NOT ${dep}_FOUND)
    find_package(${dep})
  endif()
  list(APPEND bzip2_INCLUDE_DIRS ${${dep}_INCLUDE_DIRS})
  list(APPEND bzip2_LIBRARIES ${${dep}_LIBRARIES})
endforeach()
