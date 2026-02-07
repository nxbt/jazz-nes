#include "cpu.h"

#include "bus.h"

#include <cstdint>

const uint8_t OPCODE_MASK = 0xe0;

Cpu::Cpu(Bus &bus): m_bus(bus) {}

void Cpu::tick() {
    if(m_clock_lead > 0) {
        m_clock_lead--;
    }

    ir_fetch();
    ir_decode();
}

/*
 * Fetches next instruction from the program counter (PC)
 */
void Cpu::ir_fetch() {
    m_bus.write_address(m_pc);
    m_ir = m_bus.read_data();
    m_pc++;
}

/*
 * Decodes the instruction register and executes the instruction
 */
void Cpu::ir_decode() {
    auto opcode = m_ir & OPCODE_MASK;
}

void Cpu::instr_adc() {}
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
