cmake_minimum_required(VERSION 3.10.0)
project(jazz_nes VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)

set(INC ${PROJECT_SOURCE_DIR}/include)
set(SRC ${PROJECT_SOURCE_DIR}/src)

set(INC_FILES 
    ${INC}/bus.h 
    ${INC}/cpu.h
    ${INC}/bus_component.h
    ${INC}/bus_driver.h
    ${INC}/cartridge.h
    ${INC}/file_reader.h
    ${INC}/ram.h
    ${INC}/rom.h
    ${INC}/nes.h
)
set(SRC_FILES
    ${SRC}/bus.cpp
    ${SRC}/cpu.cpp
    ${SRC}/bus_driver.cpp
    ${SRC}/bus_component.cpp
    ${SRC}/cartridge.cpp
    ${SRC}/file_reader.cpp
    ${SRC}/ram.cpp
    ${SRC}/rom.cpp
    ${SRC}/nes.cpp
)

add_executable(jazz_nes ${SRC}/main.cpp ${INC_FILES} ${SRC_FILES})
target_include_directories(jazz_nes PRIVATE ${INC} ${SRC})

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
