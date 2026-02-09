#pragma once
#include <cstdint>
#include <functional>
#include <map>

#include "bus.h"

/*
 * Representation of the NES CPU, RP2A03, a modified version of the 6502.
 * 
 * CPU behavior is emulated per instruction. Syncing with other emulated
 * hardware components is achieved by tracking how many CPU cycles have been
 * processed ahead of schedule and delaying the IR fetch accordingly.
 */
class Cpu {
public:
    Cpu(Bus &bus);
    ~Cpu();

    void tick();

private:
    Bus& m_bus;

    // program counter
    uint16_t m_pc;

    // registers: Accumulator, X, Y, Stack pointer
    uint8_t m_a, m_x, m_y, m_s;

    // status flags: Negative, oVerflow, Decimal, Interrupt disable, Zero, Carry
    bool m_flag_n, m_flag_v, m_flag_d, m_flag_i, m_flag_z, m_flag_c;

    // tracks how many cpu cycles have been processed ahead of schedule
    int m_clock_lead = 0;

    // maps 8-bit opcodes to functions for each cpu instruction
    static std::map<uint8_t, std::function<void(Cpu &)>> instr_map;

    void ir_fetch();
    void stack_push(uint8_t data);
    uint8_t stack_pull();

    // addressing modes
    static std::function<void(Cpu &)> addr_mode_r_i(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_d(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_a(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_dx(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_dy(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_ax(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_ay(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_ix(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_iy(std::function<void(Cpu &, uint8_t)> instr);

    static std::function<void(Cpu &)> addr_mode_w_d(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_w_a(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_w_dx(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_w_dy(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_w_ax(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_w_ay(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_w_ix(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_w_iy(std::function<void(Cpu &, uint8_t)> instr);

    static std::function<void(Cpu &)> addr_mode_rmw_ac(std::function<uint8_t(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_rmw_d(std::function<uint8_t(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_rmw_a(std::function<uint8_t(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_rmw_dx(std::function<uint8_t(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_rmw_ax(std::function<uint8_t(Cpu &, uint8_t)> instr);

    // instructions
    void instr_adc(uint8_t arg);
    void instr_and(uint8_t arg);
    uint8_t instr_asl(uint8_t arg);
    void instr_bcc();
    void instr_bcs();
    void instr_beq();
    void instr_bit(uint8_t arg);
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
    void instr_cmp(uint8_t arg);
    void instr_cpx(uint8_t arg);
    void instr_cpy(uint8_t arg);
    uint8_t instr_dec(uint8_t arg);
    void instr_dex();
    void instr_dey();
    void instr_eor(uint8_t arg);
    uint8_t instr_inc(uint8_t arg);
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