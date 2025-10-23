set (SOURCES 
  main.cpp)

add_executable(TaikoCV ${SOURCES})

target_link_libraries(TaikoCV ${OpenCV_LIBS} SYSTEM GAME)

include_directories(${CMAKE_SOURCE_DIR}/include/system)
include_directories(${CMAKE_SOURCE_DIR}/include/game)

add_subdirectory(system)
add_subdirectory(game)