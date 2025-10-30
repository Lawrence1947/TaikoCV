project(TaikoCV LANGUAGES CXX)

set(THIRD_PARTY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/third_party/)

set(THIRD_PARTY_SOURCES
  ${THIRD_PARTY_SOURCE_DIR}/nlohmann/json.hpp
  ${THIRD_PARTY_SOURCE_DIR}/macron/miniaudio.h
)

add_library(THIRD_PARTY INTERFACE)
target_include_directories(THIRD_PARTY INTERFACE ${THIRD_PARTY_SOURCES})