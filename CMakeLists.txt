cmake_minimum_required(VERSION 3.11)
project(paczki_plusplus C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -O3")


include(FetchContent)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

include(FetchContent)
    FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 206e1def6f888cbf69bdf0138f4e1a67a0377e4f
)
FetchContent_GetProperties(raylib)
if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING  OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src/)
set(HEADER_DIR ${CMAKE_CURRENT_LIST_DIR}/include/)

set(PROJECT_SOURCES
    ${SOURCE_DIR}/main.cc
    ${SOURCE_DIR}/json_utils.cc

    ${SOURCE_DIR}/box/instance.cc
    ${SOURCE_DIR}/box/definition.cc
    ${SOURCE_DIR}/box/list.cc

    ${SOURCE_DIR}/graphics/box.cc

    ${SOURCE_DIR}/schema/data.cc
    ${SOURCE_DIR}/schema/box_type.cc
    ${SOURCE_DIR}/schema/box_pos.cc
    ${SOURCE_DIR}/schema/sku.cc
)


set(JSON_TEST_SOURCES
    ${SOURCE_DIR}/test_json.cc
    ${SOURCE_DIR}/schema/data.cc
    ${SOURCE_DIR}/schema/box_pos.cc
    ${SOURCE_DIR}/schema/box_type.cc
    ${SOURCE_DIR}/schema/sku.cc
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIR})
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

add_executable(json_test ${JSON_TEST_SOURCES})

target_link_libraries(json_test PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(json_test PRIVATE ${HEADER_DIR})
