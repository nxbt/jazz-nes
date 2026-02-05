#pragma once
#include <cstdint>

#include "bus.h"

class Cpu {
private:
    // program counter, accumulator, x & y registers, processor status, stack pointer
    uint16_t m_pc;
    uint8_t m_a, m_x, m_y, m_p, m_s;

    Bus& m_bus;

    void tick();
    void ir_fetch();
    void ir_decode();

    void instr_adc();
    void instr_and();
    void instr_asl();
    void instr_bcc();
    void instr_bcs();
    void instr_beq();
    void instr_bit();
    void instr_bmi();
    void instr_bne();
    void instr_bpl();
    void instr_brk();
    void instr_bvc();
    void instr_bvs();
    void instr_clc();
    void instr_cld();
    void instr_cli();
    void instr_clv();
    void instr_cmp();
    void instr_cpx();
    void instr_cpy();
    void instr_dec();
    void instr_dex();
    void instr_dey();
    void instr_eor();
    void instr_inc();
    void instr_inx();
    void instr_iny();
    void instr_jmp();
    void instr_jsr();
    void instr_lda();
    void instr_ldx();
    void instr_ldy();
    void instr_lsr();
    void instr_nop();
    void instr_ora();
    void instr_pha();
    void instr_php();
    void instr_pla();
    void instr_plp();
    void instr_rol();
    void instr_ror();
    void instr_rti();
    void instr_rts();
    void instr_sbc();
    void instr_sec();
    void instr_sed();
    void instr_sei();
    void instr_sta();
    void instr_stx();
    void instr_sty();
    void instr_tax();
    void instr_tay();
    void instr_tsx();
    void instr_txa();
    void instr_txs();
    void instr_tya();

public:
    Cpu(Bus &bus);
};