set (SOURCES 
  main.cpp)

add_executable(TaikoCV ${SOURCES})

target_link_libraries(TaikoCV ${OpenCV_LIBS} SYSTEM)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(system)