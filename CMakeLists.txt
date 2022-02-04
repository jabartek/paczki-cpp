cmake_minimum_required(VERSION 3.11)
project(paczki_plusplus C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic")

if (EMSCRIPTEN) #                                                                                                                              =1           
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}    -s ENVIRONMENT=web -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1  -s MODULARIZE=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['specialHTMLTargets', 'JSEvents', 'GL', 'callMain', 'abort']\" -s ASYNCIFY")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -s ENVIRONMENT=web -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1  -s MODULARIZE=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['specialHTMLTargets', 'JSEvents', 'GL', 'callMain', 'abort']\" -s ASYNCIFY")
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
endif ()

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
    GIT_REPOSITORY https://github.com/jabartek/raylib.git
)
FetchContent_GetProperties(raylib)
if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING  OFF CACHE BOOL "" FORCE)
    add_compile_definitions(DOM_CANVAS_ID_EXTERNAL)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src/)
set(HEADER_DIR ${CMAKE_CURRENT_LIST_DIR}/include/)

set(PROJECT_SOURCES
    ${SOURCE_DIR}/main.cc
    ${SOURCE_DIR}/json_utils.cc

    ${SOURCE_DIR}/graphics/box.cc

    ${SOURCE_DIR}/pallet_viewer/state.cc

    ${SOURCE_DIR}/rendering/mode_3d.cc

    ${SOURCE_DIR}/schema/data.cc
    ${SOURCE_DIR}/schema/box_type.cc
    ${SOURCE_DIR}/schema/box_pos.cc
    ${SOURCE_DIR}/schema/sku.cc

    ${SOURCE_DIR}/ui/cursor_3d.cc
    ${SOURCE_DIR}/ui/pallet_view.cc
    ${SOURCE_DIR}/ui/rotator.cc
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
target_link_options(${PROJECT_NAME} PRIVATE -s EXPORT_NAME="paczki_view_module" --bind)


add_executable(canvas_test ${SOURCE_DIR}/canvas.cc)
target_link_libraries(canvas_test PRIVATE raylib nlohmann_json::nlohmann_json)
target_include_directories(canvas_test PRIVATE ${HEADER_DIR})
target_link_options(canvas_test PRIVATE -s EXPORT_NAME="canvas_test_module" --bind)
