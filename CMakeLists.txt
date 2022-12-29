cmake_minimum_required(VERSION 3.16)

project(lua)

file(GLOB luaSrcs lua/*.c)
list(REMOVE_ITEM luaSrcs ${CMAKE_CURRENT_LIST_DIR}/lua/lua.c)
list(REMOVE_ITEM luaSrcs ${CMAKE_CURRENT_LIST_DIR}/lua/onelua.c)

add_library(lua ${luaSrcs})

target_include_directories(lua PUBLIC lua/)
target_link_libraries(lua PUBLIC m)

project(LuaOS)

add_executable(${PROJECT_NAME}
  src/main.c
)

target_link_libraries(LuaOS PUBLIC lua)