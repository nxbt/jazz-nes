cmake_minimum_required(VERSION 3.10.0)
project(jazz_nes VERSION 0.1.0 LANGUAGES C CXX)

set(INC ${PROJECT_SOURCE_DIR}/include)
set(SRC ${PROJECT_SOURCE_DIR}/src)

set(INC_FILES ${INC}/bus.h ${INC}/cpu.h)
set(SRC_FILES ${SRC}/bus.cpp ${SRC}/cpu.cpp)

add_executable(jazz_nes ${SRC}/main.cpp ${INC_FILES} ${SRC_FILES})
target_include_directories(jazz_nes PRIVATE ${INC} ${SRC})

add_subdirectory(tests)
