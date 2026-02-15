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
    static std::function<void(Cpu &)> addr_mode_r_im(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_d(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_a(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_dx(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_dy(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_ax(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_ay(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_ix(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_iy(std::function<void(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_r_i(std::function<void(Cpu &, uint8_t)> instr);

    static std::function<void(Cpu &)> addr_mode_w_d(std::function<uint8_t(Cpu &)> instr);
    static std::function<void(Cpu &)> addr_mode_w_a(std::function<uint8_t(Cpu &)> instr);
    static std::function<void(Cpu &)> addr_mode_w_dx(std::function<uint8_t(Cpu &)> instr);
    static std::function<void(Cpu &)> addr_mode_w_dy(std::function<uint8_t(Cpu &)> instr);
    static std::function<void(Cpu &)> addr_mode_w_ax(std::function<uint8_t(Cpu &)> instr);
    static std::function<void(Cpu &)> addr_mode_w_ay(std::function<uint8_t(Cpu &)> instr);
    static std::function<void(Cpu &)> addr_mode_w_ix(std::function<uint8_t(Cpu &)> instr);
    static std::function<void(Cpu &)> addr_mode_w_iy(std::function<uint8_t(Cpu &)> instr);

    static std::function<void(Cpu &)> addr_mode_rmw_ac(std::function<uint8_t(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_rmw_d(std::function<uint8_t(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_rmw_a(std::function<uint8_t(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_rmw_dx(std::function<uint8_t(Cpu &, uint8_t)> instr);
    static std::function<void(Cpu &)> addr_mode_rmw_ax(std::function<uint8_t(Cpu &, uint8_t)> instr);

    // instructions
    static void instr_adc(Cpu cpu, uint8_t arg);
    static void instr_and(Cpu cpu, uint8_t arg);
    static uint8_t instr_asl(Cpu cpu, uint8_t arg);
    static void instr_bcc(Cpu cpu);
    static void instr_bcs(Cpu cpu);
    static void instr_beq(Cpu cpu);
    static void instr_bit(Cpu cpu, uint8_t arg);
    static void instr_bmi(Cpu cpu);
    static void instr_bne(Cpu cpu);
    static void instr_bpl(Cpu cpu);
    static void instr_brk(Cpu cpu);
    static void instr_bvc(Cpu cpu);
    static void instr_bvs(Cpu cpu);
    static void instr_clc(Cpu cpu);
    static void instr_cld(Cpu cpu);
    static void instr_cli(Cpu cpu);
    static void instr_clv(Cpu cpu);
    static void instr_cmp(Cpu cpu, uint8_t arg);
    static void instr_cpx(Cpu cpu, uint8_t arg);
    static void instr_cpy(Cpu cpu, uint8_t arg);
    static uint8_t instr_dec(Cpu cpu, uint8_t arg);
    static void instr_dex(Cpu cpu);
    static void instr_dey(Cpu cpu);
    static void instr_eor(Cpu cpu, uint8_t arg);
    static uint8_t instr_inc(Cpu cpu, uint8_t arg);
    static void instr_inx(Cpu cpu);
    static void instr_iny(Cpu cpu);
    static void instr_jmp(Cpu cpu, uint8_t arg);
    static void instr_jsr(Cpu cpu, uint8_t arg);
    static void instr_lda(Cpu cpu, uint8_t arg);
    static void instr_ldx(Cpu cpu, uint8_t arg);
    static void instr_ldy(Cpu cpu, uint8_t arg);
    static uint8_t instr_lsr(Cpu cpu, uint8_t arg);
    static void instr_nop(Cpu cpu);
    static void instr_ora(Cpu cpu, uint8_t arg);
    static void instr_pha(Cpu cpu);
    static void instr_php(Cpu cpu);
    static void instr_pla(Cpu cpu);
    static void instr_plp(Cpu cpu);
    static uint8_t instr_rol(Cpu cpu, uint8_t arg);
    static uint8_t instr_ror(Cpu cpu, uint8_t arg);
    static void instr_rti(Cpu cpu);
    static void instr_rts(Cpu cpu);
    static void instr_sbc(Cpu cpu, uint8_t arg);
    static void instr_sec(Cpu cpu);
    static void instr_sed(Cpu cpu);
    static void instr_sei(Cpu cpu);
    static uint8_t instr_sta(Cpu cpu);
    static uint8_t instr_stx(Cpu cpu);
    static uint8_t instr_sty(Cpu cpu);
    static void instr_tax(Cpu cpu);
    static void instr_tay(Cpu cpu);
    static void instr_tsx(Cpu cpu);
    static void instr_txa(Cpu cpu);
    static void instr_txs(Cpu cpu);
    static void instr_tya(Cpu cpu);
};