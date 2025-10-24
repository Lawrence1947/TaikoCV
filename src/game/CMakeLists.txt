
include_directories(${CMAKE_SOURCE_DIR}/src/game/include)

set(GAME_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/game/src)
set(GAME_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/game/include)

set(GAME_SOURCES 
  ${GAME_SOURCE_DIR}/game.cpp
  ${GAME_SOURCE_DIR}/game_loop.cpp
  ${GAME_SOURCE_DIR}/menu.cpp
  ${GAME_SOURCE_DIR}/action.cpp
  ${GAME_SOURCE_DIR}/results.cpp
)
set(GAME_HEADERS 
  ${GAME_INCLUDE_DIR}/game.h
  ${GAME_INCLUDE_DIR}/game_loop.h
  ${GAME_INCLUDE_DIR}/menu.h
  ${GAME_INCLUDE_DIR}/action.h
  ${GAME_INCLUDE_DIR}/results.h
)

include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/src/game/include)

add_library(GAME STATIC ${GAME_SOURCES} ${GAME_HEADERS})

target_link_libraries(GAME SYSTEM KERNEL)


