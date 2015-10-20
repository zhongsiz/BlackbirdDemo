cmake_minimum_required (VERSION 2.8.4)
project (Blackbird)

# 查找Boost头文件和链接库
find_package (Boost REQUIRED COMPONENTS system filesystem program_options) 
if (Boost_FOUND)
    SET (BOOST_PATH ${Boost_INCLUDE_DIRS})
    SET (BOOST_LIB ${Boost_LIBRARY_DIRS})
else (Boost_FOUND)
    message(FATAL_ERROR "Boost library not found!")
endif(Boost_FOUND)

# 查找CURL头文件和链接库
find_package (CURL REQUIRED )
if (CURL_FOUND)
    SET (CURL_PATH ${Boost_INCLUDE_DIRS})
    SET (CURL_LIB ${Boost_LIBRARY_DIRS})
else (CURL_FOUND)
    message(FATAL_ERROR "CURL library not found!")
endif(CURL_FOUND)

# 查找NCurses库
find_path(NCURSESW_PATH NAME ncurses.h HINTS /usr/include)
find_library(NCURSESW_LIB NAME ncursesw HINTS /usr/lib)
if (NCURSESW_PATH AND NCURSESW_LIB)
    SET(NCURSESW_FOUND TRUE)
else (NCURSESW_PATH AND NCURSESW_LIB)
    message("NCursesw library not found!")
endif(NCURSESW_PATH AND NCURSESW_LIB)

# 设置输出目录
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置全局目录
SET(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET(COMMON_LIB ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# 全局包含路径
INCLUDE_DIRECTORIES("${ROOT_PATH}")
INCLUDE_DIRECTORIES("${BOOST_PATH}")
INCLUDE_DIRECTORIES("${CURL_PATH}")

# 设置C++编译选项
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wno-unused-variable -Wno-unused-function -O2 -std=c++11" )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wno-unused-variable -Wno-unused-function -std=c++11" )

# 编译类型为Debug
SET( CMAKE_BUILD_TYPE Debug )

# 编译目录
ADD_SUBDIRECTORY(src/common)
ADD_SUBDIRECTORY(src)
