cmake_minimum_required(VERSION 3.10.0)
project(jazz_nes VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)

set(INC ${PROJECT_SOURCE_DIR}/include)
set(SRC ${PROJECT_SOURCE_DIR}/src)

set(INC_FILES 
    ${INC}/bus.h 
    ${INC}/cpu.h
    ${INC}/bus_component.h
)
set(SRC_FILES
    ${SRC}/bus.cpp
    ${SRC}/cpu.cpp
)

add_executable(jazz_nes ${SRC}/main.cpp ${INC_FILES} ${SRC_FILES})
target_include_directories(jazz_nes PRIVATE ${INC} ${SRC})

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
