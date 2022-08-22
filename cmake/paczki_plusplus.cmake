cmake_minimum_required(VERSION 3.11)
project(paczki_plusplus CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -Wall -Wextra -Wpedantic")

if (EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fwasm-exceptions")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fwasm-exceptions ")
else()
    message("Using system compilers.")
endif(EMSCRIPTEN)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../src/)

add_executable(${PROJECT_NAME}
   ${SOURCE_DIR}/main.cc
   ${SOURCE_DIR}/bind/stores.cc
)


if (EMSCRIPTEN)
target_link_libraries(${PROJECT_NAME} PRIVATE paczki_lib embind)
target_link_options(${PROJECT_NAME} PRIVATE -sEXPORT_NAME=${PROJECT_NAME})
target_link_options(${PROJECT_NAME} PRIVATE -fwasm-exceptions -sENVIRONMENT=web -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sMODULARIZE=1 -sEXPORTED_RUNTIME_METHODS=['specialHTMLTargets','JSEvents','GL','callMain','abort','FS'] -sFORCE_FILESYSTEM=1 -sEXIT_RUNTIME=1)
else()
target_link_libraries(${PROJECT_NAME} PRIVATE paczki_lib)
endif()