set (SOURCES 
  main.cpp)

add_executable(TaikoCV ${SOURCES})

target_link_libraries(TaikoCV ${OpenCV_LIBS})