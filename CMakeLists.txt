cmake_minimum_required(VERSION 3.5)
project(mark_learn_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(fmt)
set(test_sema_lib Threads::Threads fmt::fmt)
set(IGNORE_FILE_LIST
)

find_package(Threads REQUIRED)

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
foreach( sourcefile ${APP_SOURCES} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR}/src ${sourcefile})
    if(${filename} IN_LIST IGNORE_FILE_LIST)
        message(${filename} " ignore, no compile")
        continue()
    endif()
    string( REPLACE ".cpp" "" file ${filename} )
    add_executable( ${file} ${sourcefile} )
    if(DEFINED ${file}_lib)
        message(${file}_lib " defined")
        target_link_libraries( ${file} PRIVATE ${${file}_lib} )
    endif()
    target_link_libraries( ${file} PRIVATE Threads::Threads )
endforeach( sourcefile ${APP_SOURCES} )
