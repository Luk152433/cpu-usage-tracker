cmake_minimum_required(VERSION 3.15)


option(TestOption "TestOption" OFF)
if(TestOption MATCHES OFF)
project(Project VERSION 1.0)
endif()
if(TestOption MATCHES ON)
project(TestProject VERSION 1.0)
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
message(STATUS ${CMAKE_C_COMPILER})
if(CMAKE_C_COMPILER_LOADED)
     message(STATUS "Compiler path: ${CMAKE_C_COMPILER}")
     message(STATUS "Compiler ID: ${CMAKE_C_COMPILER_ID}")
     message(STATUS "Compiler version:${CMAKE_C_COMPILER_VERSION}")
     message(STATUS "Compiler is part of GCC: ${CMAKE_COMPILER_IS_GNUCC}")
endif()

set(C_FLAGS)


# append global compiler flags to list
add_library(compiler_flags INTERFACE)

# append compile flags depending on the selected compiler and build type
if(CMAKE_C_COMPILER_ID MATCHES GNU)
  list(APPEND C_FLAGS "-pthread" "-Wall" "-Wextra"   )
endif()

if(CMAKE_C_COMPILER_ID MATCHES Clang)
  list(APPEND C_FLAGS "-pthread" "-Weverything")
endif()
target_compile_options(compiler_flags INTERFACE ${C_FLAGS}
)

if(TestOption MATCHES OFF)
add_subdirectory(src)

add_executable(Project main.c)

target_link_libraries(Project PUBLIC Functions compiler_flags)

target_include_directories(Project PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            )
                                                   
endif()
if(TestOption MATCHES ON)
    add_subdirectory(src)   
    add_subdirectory(test)  
    add_executable(TestProject ./test/test.c)
    target_link_libraries(TestProject PUBLIC  Functions compiler_flags)                                           
    target_include_directories(TestProject PUBLIC
                          "${PROJECT_BINARY_DIR}"
    )
    endif()