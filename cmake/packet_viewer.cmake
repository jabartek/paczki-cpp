cmake_minimum_required(VERSION 3.11)
if (EMSCRIPTEN)
project(packet_viewer CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -Wextra -Wpedantic")


add_executable(${PROJECT_NAME} ../src/packet_viewer.cc
   ../src/bind/stores.cc
   ../src/packet_viewer/state.cc
   )

target_link_libraries(${PROJECT_NAME} PRIVATE paczki_lib embind)

target_link_options(${PROJECT_NAME} PRIVATE -sEXPORT_NAME=${PROJECT_NAME})
target_link_options(${PROJECT_NAME} PRIVATE -fwasm-exceptions -sENVIRONMENT=web -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sMODULARIZE=1 -sEXPORTED_RUNTIME_METHODS=['specialHTMLTargets','JSEvents','GL','callMain','abort'])
else()
message("Not building packet_viewer - it's web only part of the project.")
endif()