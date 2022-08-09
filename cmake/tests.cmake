cmake_minimum_required(VERSION 3.11)
project(paczki_tests CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(ut
  GIT_REPOSITORY https://github.com/boost-ext/ut.git
  GIT_TAG v1.1.9
  GIT_SHALLOW On
)

FetchContent_GetProperties(ut)
if(NOT ut_POPULATED)
  FetchContent_Populate(ut)
  add_subdirectory(${ut_SOURCE_DIR} ${ut_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/../tests/)

add_executable(${PROJECT_NAME} ${TEST_DIR}/json_load.cc)

if (EMSCRIPTEN)
target_link_libraries(${PROJECT_NAME} PRIVATE nodefs.js)
target_link_options(${PROJECT_NAME} PRIVATE -sNODERAWFS=1)
endif ()

target_link_libraries(${PROJECT_NAME} PUBLIC paczki_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::ut)
