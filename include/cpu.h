#pragma once
#include <cstdint>
#include <functional>
#include <unordered_map>

#include "bus.h"

class Cpu {
public:
    Cpu(Bus &bus);
    ~Cpu();

    void tick();

private:
    Bus& m_bus;

    // program counter, accumulator, x & y registers, processor status, stack pointer, instruction register
    uint16_t m_pc;
    uint8_t m_a, m_x, m_y, m_p, m_s, m_ir;

    bool m_flag_n, m_flag_v, m_flag_d, m_flag_i, m_flag_z, m_flag_c;

    int m_clock_lead = 0;

    const static std::unordered_map<uint8_t, std::function<void()>> instr_map;

    void ir_fetch();
    void ir_decode();

    // add with carry
    void instr_adc(uint8_t arg);
    void instr_adc_i();
    void instr_adc_d();
    void instr_adc_dx();
    void instr_adc_a();
    void instr_adc_ax();
    void instr_adc_ay();
    void instr_adc_ix();
    void instr_adc_iy();

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
};