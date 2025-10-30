set (SOURCES 
  main.cpp)

add_executable(TaikoCV ${SOURCES})

target_link_libraries(TaikoCV ${OpenCV_LIBS} SYSTEM GAME KERNEL THIRD_PARTY)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(system)
add_subdirectory(kernel)
add_subdirectory(game)
add_subdirectory(third_party)