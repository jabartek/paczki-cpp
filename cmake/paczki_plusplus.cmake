cmake_minimum_required(VERSION 3.11)
project(paczki_plusplus CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3  -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3  -Wall -Wextra -Wpedantic")

if (EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fwasm-exceptions")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fwasm-exceptions ")
else()
    message("Using system compilers.")
endif(EMSCRIPTEN)

add_executable(${PROJECT_NAME} ../src/main.cc
   ../src/bind/stores.cc)


if (EMSCRIPTEN)
target_link_libraries(${PROJECT_NAME} PRIVATE paczki_lib embind)
target_link_options(${PROJECT_NAME} PRIVATE -sEXPORT_NAME=${PROJECT_NAME})
target_link_options(${PROJECT_NAME} PRIVATE -fwasm-exceptions -sENVIRONMENT=web -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sMODULARIZE=1 -sEXPORTED_RUNTIME_METHODS=['specialHTMLTargets','JSEvents','GL','callMain','abort'] -sFORCE_FILESYSTEM=1)
else()
target_link_libraries(${PROJECT_NAME} PRIVATE paczki_lib)
endif()