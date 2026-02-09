#include "cpu.h"

#include "bus.h"

#include <cstdint>
#include <functional>
#include <map>

std::map<uint8_t, std::function<void(Cpu &)>> Cpu::instr_map = {
    {0x00, instr_brk},
    {0x69, addr_mode_i(instr_adc)},
};

Cpu::Cpu(Bus &bus): m_bus(bus) {}

void Cpu::tick() {
    if(m_clock_lead > 0) {
        m_clock_lead--;
    }

    ir_fetch();
}

// Fetches and executes next instruction from program counter (PC)
void Cpu::ir_fetch() {
    uint16_t ir = m_bus.read_data(m_pc++);
    instr_map[ir](*this);
}

// immidiate addressing mode wrapper for any instruction
std::function<void(Cpu &)> Cpu::addr_mode_i(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {
        instr(cpu, cpu.m_bus.read_data(cpu.m_pc++));
    };
}

// zero page addressing mode wrapper for any instruction
std::function<void(Cpu &)> Cpu::addr_mode_d(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {
        auto addr = cpu.m_bus.read_data(cpu.m_pc++);
        instr(cpu, cpu.m_bus.read_data(addr));
    };
}

// absolute addressing mode wrapper for any instruction
std::function<void(Cpu &)> Cpu::addr_mode_a(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {
        uint16_t l_addr = cpu.m_bus.read_data(cpu.m_pc++);
        uint16_t h_addr = cpu.m_bus.read_data(cpu.m_pc++);
        instr(cpu, cpu.m_bus.read_data((h_addr << 8) | l_addr));
    };
}

// zero page x indexed addressing mode wrapper for any instruction
static std::function<void(Cpu &)> addr_mode_dx(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {

    };
}

// zero page y indexed addressing mode wrapper for any instruction
static std::function<void(Cpu &)> addr_mode_dy(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {

    };
}


// absolute x indexed addressing mode wrapper for any instruction
static std::function<void(Cpu &)> addr_mode_ax(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {

    };
}

// absolute y indexed addressing mode wrapper for any instruction
static std::function<void(Cpu &)> addr_mode_ay(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {

    };
}

// indirect x indexed addressing mode wrapper for any instruction
static std::function<void(Cpu &)> addr_mode_ix(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {

    };
}

// indirect y index addressing mode wrapper for any instruction
static std::function<void(Cpu &)> addr_mode_iy(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {

    };
}

// add with carry
void Cpu::instr_adc(uint8_t arg) {
    uint16_t result = m_a + arg + m_flag_c;
    m_a = result;

    m_flag_c = result > 0xFF;
    m_flag_z = result == 0;
    m_flag_v = (result ^ m_a) & (result ^ arg) & 0x80;
    m_flag_n = m_a & 0x80;
}

void Cpu::instr_and() {}
void Cpu::instr_asl() {}
void Cpu::instr_bcc() {}
void Cpu::instr_bcs() {}
void Cpu::instr_beq() {}
void Cpu::instr_bit() {}
void Cpu::instr_bmi() {}
void Cpu::instr_bne() {}
void Cpu::instr_bpl() {}
void Cpu::instr_brk() {}
void Cpu::instr_bvc() {}
void Cpu::instr_bvs() {}
void Cpu::instr_clc() {}
void Cpu::instr_cld() {}
void Cpu::instr_cli() {}
void Cpu::instr_clv() {}
void Cpu::instr_cmp() {}
void Cpu::instr_cpx() {}
void Cpu::instr_cpy() {}
void Cpu::instr_dec() {}
void Cpu::instr_dex() {}
void Cpu::instr_dey() {}
void Cpu::instr_eor() {}
void Cpu::instr_inc() {}
void Cpu::instr_inx() {}
void Cpu::instr_iny() {}
void Cpu::instr_jmp() {}
void Cpu::instr_jsr() {}
void Cpu::instr_lda() {}
void Cpu::instr_ldx() {}
void Cpu::instr_ldy() {}
void Cpu::instr_lsr() {}
void Cpu::instr_nop() {}
void Cpu::instr_ora() {}
void Cpu::instr_pha() {}
void Cpu::instr_php() {}
void Cpu::instr_pla() {}
void Cpu::instr_plp() {}
void Cpu::instr_rol() {}
void Cpu::instr_ror() {}
void Cpu::instr_rti() {}
void Cpu::instr_rts() {}
void Cpu::instr_sbc() {}
void Cpu::instr_sec() {}
void Cpu::instr_sed() {}
void Cpu::instr_sei() {}
void Cpu::instr_sta() {}
void Cpu::instr_stx() {}
void Cpu::instr_sty() {}
void Cpu::instr_tax() {}
void Cpu::instr_tay() {}
void Cpu::instr_tsx() {}
void Cpu::instr_txa() {}
void Cpu::instr_txs() {}
void Cpu::instr_tya() {}
