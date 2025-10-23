
include_directories(${CMAKE_SOURCE_DIR}/src/system/include)

set(SYSTEM_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/system/src)
set(SYSTEM_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/system/include)

set(SYSTEM_SOURCES ${SYSTEM_SOURCE_DIR}/screen.cpp)
set(SYSTEM_HEADERS ${SYSTEM_INCLUDE_DIR}/screen.h)

add_library(SYSTEM STATIC ${SYSTEM_SOURCES} ${SYSTEM_HEADERS})

find_package(X11 REQUIRED)

target_link_libraries(SYSTEM PRIVATE X11::X11 X11::Xrandr)
