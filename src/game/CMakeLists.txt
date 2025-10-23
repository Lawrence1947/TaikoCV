
include_directories(${CMAKE_SOURCE_DIR}/src/game/include)

set(GAME_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/game/src)
set(GAME_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/game/include)

set(GAME_SOURCES ${GAME_SOURCE_DIR}/game.cpp)
set(GAME_HEADERS ${GAME_INCLUDE_DIR}/game.h)

add_library(GAME STATIC ${GAME_SOURCES} ${GAME_HEADERS})


