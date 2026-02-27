add_executable(cpu_instr_tests cpu_instr_tests.cpp ${INC_FILES} ${SRC_FILES})
target_include_directories(cpu_instr_tests PRIVATE ${INC} ${SRC})
file(COPY test_roms DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME CpuInstructionTests COMMAND cpu_instr_tests)