
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules" ${CMAKE_MODULE_PATH})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

add_library(typegrind-logger-buffered_binary STATIC
  logger/buffered_binary.cpp
  buffered_binary/log_entry.cpp
  buffered_binary/logger.cpp
  buffered_binary/thread_buffer.cpp
)

set_property(TARGET typegrind-logger-buffered_binary PROPERTY CXX_STANDARD 14)

find_package(Ejdb REQUIRED)
include_directories(${EJDB_INCLUDE_DIR})

add_executable(bb-to-db
        buffered_binary/log_entry.cpp
        converter/callstack_entry.cpp
        converter/loader.cpp
        converter/main.cpp
        converter/memory_entry.cpp
        )


set_property(TARGET bb-to-db PROPERTY CXX_STANDARD 14)
target_link_libraries(bb-to-db ${EJDB_LIBRARIES})
