add_library(Functions thread.c reader.c printer.c analyzer.c buffer.c)
target_include_directories(Functions
          PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/
          )

target_link_libraries(Functions compiler_flags)          