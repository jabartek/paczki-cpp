cmake_minimum_required(VERSION 3.11)
project(paczki_lib CXX)

if (EMSCRIPTEN)
    message("Using Emscripten.")
    add_compile_definitions(EMSCRIPTEN=1)
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fwasm-exceptions")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fwasm-exceptions")
else()
    message("Using system compilers.")
endif(EMSCRIPTEN)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g  -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -g  -Wall -Wextra -Wpedantic")

include(FetchContent)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.5
  GIT_SHALLOW On
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

include(FetchContent)
    FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/jabartek/raylib.git
    GIT_SHALLOW On
)
FetchContent_GetProperties(raylib)
if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING  OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    if(EMSCRIPTEN)
        # add_compile_definitions(DOM_CANVAS_ID_EXTERNAL)
    endif()
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

include(FetchContent)
    FetchContent_Declare(
    lodepng
    GIT_REPOSITORY https://github.com/jabartek/lodepng-fetchable.git
    GIT_SHALLOW On
)
FetchContent_GetProperties(lodepng)
if (NOT lodepng_POPULATED)
    FetchContent_Populate(lodepng)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    add_subdirectory(${lodepng_SOURCE_DIR} ${lodepng_BINARY_DIR} EXCLUDE_FROM_ALL)
    include_directories(${lodepng_SOURCE_DIR}/include)
endif()

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../src/)
set(HEADER_DIR ${CMAKE_CURRENT_LIST_DIR}/../include/)

set(PROJECT_SOURCES
    ${SOURCE_DIR}/json_utils.cc

    ${SOURCE_DIR}/bind/bind.cc
    ${SOURCE_DIR}/bind/stores.cc

    ${SOURCE_DIR}/graphics/box.cc

    ${SOURCE_DIR}/lib/raymath_implementation.cc

    ${SOURCE_DIR}/rendering/mode_3d.cc

    ${SOURCE_DIR}/schema/data.cc
    ${SOURCE_DIR}/schema/box_type.cc
    ${SOURCE_DIR}/schema/box_pos.cc
    ${SOURCE_DIR}/schema/sku.cc

    ${SOURCE_DIR}/ui/cursor_3d.cc
    ${SOURCE_DIR}/ui/handlers.cc
    ${SOURCE_DIR}/ui/pallet_view.cc
    ${SOURCE_DIR}/ui/rotator.cc

    ${SOURCE_DIR}/utils/png.cc
)

add_library(${PROJECT_NAME} ${PROJECT_SOURCES})

if (EMSCRIPTEN)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib nlohmann_json::nlohmann_json lodepng embind)
else()
target_link_libraries(${PROJECT_NAME} PUBLIC raylib nlohmann_json::nlohmann_json lodepng)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${HEADER_DIR} 
)

if (EMSCRIPTEN)
target_link_options(${PROJECT_NAME} PRIVATE -fwasm-exceptions -sENVIRONMENT=web -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sEXPORTED_RUNTIME_METHODS=['specialHTMLTargets','JSEvents','GL','callMain','abort'] -sFORCE_FILESYSTEM=1)
else()
endif()