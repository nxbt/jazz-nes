#include "cpu.h"

#include "bus.h"

#include <cstdint>
#include <functional>
#include <unordered_map>

auto Cpu::instr_map = {
    {0x00, Cpu::instr_brk},
    {0x69, Cpu::instr_adc_i},
    {0x65, Cpu::instr_adc_d},
    {0x75, Cpu::instr_adc_dx},
    {0x6D, Cpu::instr_adc_a},
    {0x7D, Cpu::instr_adc_ax},
    {0x79, Cpu::instr_adc_ay},
    {0x61, Cpu::instr_adc_ix},
    {0x71, Cpu::instr_adc_iy},
};

Cpu::Cpu(Bus &bus): m_bus(bus) {}

void Cpu::tick() {
    if(m_clock_lead > 0) {
        m_clock_lead--;
    }

    ir_fetch();
    ir_decode();
}

/*
 * Fetches next instruction byte from the program counter (PC)
 */
void Cpu::ir_fetch() {
    m_ir = m_bus.read_data(m_pc++);
}

/*
 * Decodes the instruction register and executes the instruction
 */
void Cpu::ir_decode() {
    instr_map[m_ir]();
}

void Cpu::instr_adc(u_int8_t arg) {
    uint16_t result = m_a + arg + m_flag_c;
    m_a = result;

    m_flag_c = result > 0xFF;
    m_flag_z = result == 0;
    m_flag_v = (result ^ m_a) & (result ^ arg) & 0x80;
    m_flag_n = m_a & 0x80;
}
void Cpu::instr_adc_i() {
    instr_adc(m_bus.read_data(m_pc++));
}
void Cpu::instr_adc_d() {}
void Cpu::instr_adc_dx() {}
void Cpu::instr_adc_a() {}
void Cpu::instr_adc_ax() {}
void Cpu::instr_adc_ay() {}
void Cpu::instr_adc_ix() {}
void Cpu::instr_adc_iy() {}

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
