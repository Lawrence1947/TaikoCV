
include_directories(${CMAKE_SOURCE_DIR}/src/kernel/include)

set(KERNEL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/kernel/src)
set(KERNEL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/kernel/include)

set(KERNEL_SOURCES 
  ${KERNEL_SOURCE_DIR}/timer.cpp
)
set(KERNEL_HEADERS 
  ${KERNEL_INCLUDE_DIR}/timer.h
)

add_library(KERNEL STATIC ${KERNEL_SOURCES} ${KERNEL_HEADERS})