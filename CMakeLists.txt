cmake_minimum_required(VERSION 3.11)
project(paczki_plusplus CXX)

if (EMSCRIPTEN)
    message("Using Emscripten.")
    add_compile_definitions(EMSCRIPTEN=1)
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
else()
    message("Using system compilers.")
endif(EMSCRIPTEN)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

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
        add_compile_definitions(DOM_CANVAS_ID_EXTERNAL)
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

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src/)
set(HEADER_DIR ${CMAKE_CURRENT_LIST_DIR}/include/)

set(PROJECT_SOURCES
    ${SOURCE_DIR}/main.cc
    ${SOURCE_DIR}/json_utils.cc

    ${SOURCE_DIR}/bind/bind.cc

    ${SOURCE_DIR}/graphics/box.cc

    ${SOURCE_DIR}/lib/raymath_implementation.cc

    ${SOURCE_DIR}/pallet_viewer/state.cc

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

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

if (EMSCRIPTEN)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib nlohmann_json::nlohmann_json lodepng embind)
else()
target_link_libraries(${PROJECT_NAME} PRIVATE raylib nlohmann_json::nlohmann_json lodepng)
endif()

# if (EMSCRIPTEN)
# target_link_libraries(${PROJECT_NAME} PRIVATE raylib nlohmann_json::nlohmann_json embind)
# else()
# target_link_libraries(${PROJECT_NAME} PRIVATE raylib nlohmann_json::nlohmann_json)
# endif()


target_include_directories(${PROJECT_NAME} PRIVATE 
    ${HEADER_DIR} 
)

if (EMSCRIPTEN)
target_link_options(${PROJECT_NAME} PRIVATE -sEXPORT_NAME="paczki_view_module" -sENVIRONMENT=web -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sALLOW_MEMORY_GROWTH=1  -sMODULARIZE=1 -sEXPORTED_RUNTIME_METHODS=['specialHTMLTargets','JSEvents','GL','callMain','abort'] -sASYNCIFY -sNO_DISABLE_EXCEPTION_CATCHING)
else()
# target_link_options(${PROJECT_NAME} PRIVATE -Wl,-pdb=)

endif()

# add_executable(canvas_test ${SOURCE_DIR}/canvas.cc)
# target_link_libraries(canvas_test PRIVATE raylib nlohmann_json::nlohmann_json embind)
# target_include_directories(canvas_test PRIVATE ${HEADER_DIR})
# target_link_options(canvas_test PRIVATE -sEXPORT_NAME="canvas_test_module" -sENVIRONMENT=web -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sALLOW_MEMORY_GROWTH=1  -sMODULARIZE=1 -sEXPORTED_RUNTIME_METHODS=['specialHTMLTargets','JSEvents','GL','callMain','abort'] -sASYNCIFY)
