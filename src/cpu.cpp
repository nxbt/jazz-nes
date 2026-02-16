#include "cpu.h"

#include "bus.h"

#include <cstdint>
#include <functional>
#include <map>

std::map<uint8_t, std::function<void(Cpu &)>> Cpu::instr_map = {
    {0x69, addr_mode_r_im(instr_adc)},
    {0x65, addr_mode_r_d(instr_adc)},
    {0x75, addr_mode_r_dx(instr_adc)},
    {0x6D, addr_mode_r_a(instr_adc)},
    {0x7D, addr_mode_r_ax(instr_adc)},
    {0x79, addr_mode_r_ay(instr_adc)},
    {0x61, addr_mode_r_ix(instr_adc)},
    {0x71, addr_mode_r_iy(instr_adc)},
    {0x29, addr_mode_r_im(instr_and)},
    {0x25, addr_mode_r_d(instr_and)},
    {0x35, addr_mode_r_dx(instr_and)},
    {0x2D, addr_mode_r_a(instr_and)},
    {0x3D, addr_mode_r_ax(instr_and)},
    {0x39, addr_mode_r_ay(instr_and)},
    {0x21, addr_mode_r_ix(instr_and)},
    {0x31, addr_mode_r_iy(instr_and)},
    {0x0A, addr_mode_rmw_ac(instr_asl)},
    {0x06, addr_mode_rmw_d(instr_asl)},
    {0x16, addr_mode_rmw_dx(instr_asl)},
    {0x0E, addr_mode_rmw_a(instr_asl)},
    {0x1E, addr_mode_rmw_ax(instr_asl)},
    {0x90, instr_bcc},
    {0xB0, instr_bcs},
    {0xF0, instr_beq},
    {0x24, addr_mode_r_d(instr_bit)},
    {0x2C, addr_mode_r_a(instr_bit)},
    {0x30, instr_bmi},
    {0xD0, instr_bne},
    {0x10, instr_bpl},
    {0x00, instr_brk},
    {0x50, instr_bvc},
    {0x70, instr_bvs},
    {0x18, instr_clc},
    {0xD8, instr_cld},
    {0x58, instr_cli},
    {0xB8, instr_clv},
    {0xC9, addr_mode_r_im(instr_cmp)},
    {0xC5, addr_mode_r_d(instr_cmp)},
    {0xD5, addr_mode_r_dx(instr_cmp)},
    {0xCD, addr_mode_r_a(instr_cmp)},
    {0xDD, addr_mode_r_ax(instr_cmp)},
    {0xD9, addr_mode_r_ay(instr_cmp)},
    {0xC1, addr_mode_r_ix(instr_cmp)},
    {0xD1, addr_mode_r_iy(instr_cmp)},
    {0xE0, addr_mode_r_im(instr_cpx)},
    {0xE4, addr_mode_r_d(instr_cpx)},
    {0xEC, addr_mode_r_a(instr_cpx)},
    {0xC0, addr_mode_r_im(instr_cpy)},
    {0xC4, addr_mode_r_d(instr_cpy)},
    {0xCC, addr_mode_r_a(instr_cpy)},
    {0xC6, addr_mode_rmw_d(instr_dec)},
    {0xD6, addr_mode_rmw_dx(instr_dec)},
    {0xCE, addr_mode_rmw_a(instr_dec)},
    {0xDE, addr_mode_rmw_ax(instr_dec)},
    {0xCA, instr_dex},
    {0x88, instr_dey},
    {0x49, addr_mode_r_im(instr_eor)},
    {0x45, addr_mode_r_d(instr_eor)},
    {0x55, addr_mode_r_dx(instr_eor)},
    {0x4D, addr_mode_r_a(instr_eor)},
    {0x5D, addr_mode_r_ax(instr_eor)},
    {0x59, addr_mode_r_ay(instr_eor)},
    {0x41, addr_mode_r_ix(instr_eor)},
    {0x51, addr_mode_r_iy(instr_eor)},
    {0xE6, addr_mode_rmw_d(instr_inc)},
    {0xF6, addr_mode_rmw_dx(instr_inc)},
    {0xEE, addr_mode_rmw_a(instr_inc)},
    {0xFE, addr_mode_rmw_ax(instr_inc)},
    {0xE8, instr_inx},
    {0xC8, instr_iny},
    {0x4C, addr_mode_r_a(instr_jmp)},
    {0x6C, addr_mode_r_i(instr_jmp)},
    {0x20, addr_mode_r_a(instr_jsr)},
    {0xA9, addr_mode_r_im(instr_lda)},
    {0xA5, addr_mode_r_d(instr_lda)},
    {0xB5, addr_mode_r_dx(instr_lda)},
    {0xAD, addr_mode_r_a(instr_lda)},
    {0xBD, addr_mode_r_ax(instr_lda)},
    {0xB9, addr_mode_r_ay(instr_lda)},
    {0xA1, addr_mode_r_ix(instr_lda)},
    {0xB1, addr_mode_r_iy(instr_lda)},
    {0xA2, addr_mode_r_im(instr_ldx)},
    {0xA6, addr_mode_r_d(instr_ldx)},
    {0xB6, addr_mode_r_dy(instr_ldx)},
    {0xAE, addr_mode_r_a(instr_ldx)},
    {0xBE, addr_mode_r_ay(instr_ldx)},
    {0xA0, addr_mode_r_im(instr_ldy)},
    {0xA4, addr_mode_r_d(instr_ldy)},
    {0xB4, addr_mode_r_dx(instr_ldy)},
    {0xAC, addr_mode_r_a(instr_ldy)},
    {0xBC, addr_mode_r_ax(instr_ldy)},
    {0x4A, addr_mode_rmw_ac(instr_lsr)},
    {0x46, addr_mode_rmw_d(instr_lsr)},
    {0x56, addr_mode_rmw_dx(instr_lsr)},
    {0x4E, addr_mode_rmw_a(instr_lsr)},
    {0x5E, addr_mode_rmw_ax(instr_lsr)},
    {0xEA, instr_nop},
    {0x09, addr_mode_r_im(instr_ora)},
    {0x05, addr_mode_r_d(instr_ora)},
    {0x15, addr_mode_r_dx(instr_ora)},
    {0x0D, addr_mode_r_a(instr_ora)},
    {0x1D, addr_mode_r_ax(instr_ora)},
    {0x19, addr_mode_r_ay(instr_ora)},
    {0x01, addr_mode_r_ix(instr_ora)},
    {0x11, addr_mode_r_iy(instr_ora)},
    {0x48, instr_pha},
    {0x08, instr_php},
    {0x68, instr_pla},
    {0x28, instr_plp},
    {0x28, instr_plp},
    {0x2A, addr_mode_rmw_ac(instr_rol)},
    {0x26, addr_mode_rmw_d(instr_rol)},
    {0x36, addr_mode_rmw_dx(instr_rol)},
    {0x2E, addr_mode_rmw_a(instr_rol)},
    {0x3E, addr_mode_rmw_ax(instr_rol)},
    {0x6A, addr_mode_rmw_ac(instr_ror)},
    {0x66, addr_mode_rmw_d(instr_ror)},
    {0x76, addr_mode_rmw_dx(instr_ror)},
    {0x6E, addr_mode_rmw_a(instr_ror)},
    {0x7E, addr_mode_rmw_ax(instr_ror)},
    {0x40, instr_rti},
    {0x60, instr_rts},
    {0xE9, addr_mode_r_im(instr_sbc)},
    {0xE5, addr_mode_r_d(instr_sbc)},
    {0xF5, addr_mode_r_dx(instr_sbc)},
    {0xED, addr_mode_r_a(instr_sbc)},
    {0xFD, addr_mode_r_ax(instr_sbc)},
    {0xF9, addr_mode_r_ay(instr_sbc)},
    {0xE1, addr_mode_r_ix(instr_sbc)},
    {0xF1, addr_mode_r_iy(instr_sbc)},
    {0x38, instr_sec},
    {0xF8, instr_sed},
    {0x78, instr_sei},
    {0x85, addr_mode_w_d(instr_sta)},
    {0x95, addr_mode_w_dx(instr_sta)},
    {0x8D, addr_mode_w_a(instr_sta)},
    {0x9D, addr_mode_w_ax(instr_sta)},
    {0x99, addr_mode_w_ay(instr_sta)},
    {0x81, addr_mode_w_ix(instr_sta)},
    {0x91, addr_mode_w_iy(instr_sta)},
    {0x86, addr_mode_w_d(instr_stx)},
    {0x96, addr_mode_w_dy(instr_stx)},
    {0x8E, addr_mode_w_a(instr_stx)},
    {0x84, addr_mode_w_d(instr_sty)},
    {0x94, addr_mode_w_dx(instr_sty)},
    {0x8C, addr_mode_w_a(instr_sty)},
    {0xAA, instr_tax},
    {0xA8, instr_tay},
    {0xBA, instr_tsx},
    {0x8A, instr_txa},
    {0x9A, instr_txs},
    {0x98, instr_tya},
};

Cpu::Cpu(Bus &bus): m_bus(bus) {}

Cpu::~Cpu() {}

void Cpu::tick() {
    if(m_clock_lead > 0) {
        m_clock_lead--;
    }

    ir_fetch();
}

// fetches and executes next instruction from program counter (PC)
void Cpu::ir_fetch() {
    uint16_t ir = m_bus.read_data(m_pc++);
    instr_map[ir](*this);
}

// pushes a byte to the stack
void Cpu::stack_push(uint8_t data) {
    m_bus.write_data(0x0100 + m_s--, data);
}

// pulls a byte from the stack
uint8_t Cpu::stack_pull() {
    return m_bus.read_data(0x0100 + ++m_s);
}

// immidiate addressing mode wrapper for read instruction
std::function<void(Cpu &)> Cpu::addr_mode_r_im(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {
        instr(cpu, cpu.m_bus.read_data(cpu.m_pc++));
    };
}

// zero page addressing mode wrapper for read instruction
std::function<void(Cpu &)> Cpu::addr_mode_r_d(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {
        uint8_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        instr(cpu, cpu.m_bus.read_data(addr));
    };
}

// absolute addressing mode wrapper for read instruction
std::function<void(Cpu &)> Cpu::addr_mode_r_a(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {
        uint16_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr |= cpu.m_bus.read_data(cpu.m_pc++) << 8;
        instr(cpu, cpu.m_bus.read_data(addr));
    };
}

// zero page x indexed addressing mode wrapper for read instruction
std::function<void(Cpu &)> Cpu::addr_mode_r_dx(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {
        uint8_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr += cpu.m_x;
        instr(cpu, cpu.m_bus.read_data(addr));
    };
}

// zero page y indexed addressing mode wrapper for read instruction
std::function<void(Cpu &)> Cpu::addr_mode_r_dy(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {
        uint8_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr += cpu.m_y;
        instr(cpu, cpu.m_bus.read_data(addr));
    };
}


// absolute x indexed addressing mode wrapper for read instruction
std::function<void(Cpu &)> Cpu::addr_mode_r_ax(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {
        uint16_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr |= cpu.m_bus.read_data(cpu.m_pc++) << 8;
        addr += cpu.m_x;
        instr(cpu, cpu.m_bus.read_data(addr));
    };
}

// absolute y indexed addressing mode wrapper for read instruction
std::function<void(Cpu &)> Cpu::addr_mode_r_ay(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {
        uint16_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr |= cpu.m_bus.read_data(cpu.m_pc++) << 8;
        addr += cpu.m_y;
        instr(cpu, cpu.m_bus.read_data(addr));
    };
}

// indirect addressing mode wrapper for read instructions
std::function<void(Cpu &)> Cpu::addr_mode_r_i(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu cpu) -> void {
        uint16_t ptr_addr = cpu.m_bus.read_data(cpu.m_pc++);
        ptr_addr |= cpu.m_bus.read_data(cpu.m_pc++) << 8;
        uint16_t addr = cpu.m_bus.read_data(ptr_addr);
        addr |= cpu.m_bus.read_data(((ptr_addr + 1) & 0x0F ) | (ptr_addr & 0xF0)) << 8;
        instr(cpu, cpu.m_bus.read_data(addr));
    };
}

// indirect x indexed addressing mode wrapper for read instruction
std::function<void(Cpu &)> Cpu::addr_mode_r_ix(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {

    };
}

// indirect y index addressing mode wrapper for read instruction
std::function<void(Cpu &)> Cpu::addr_mode_r_iy(std::function<void(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {

    };
}

// accumulator addressing mode wrapper for read-modify-write instructions
std::function<void(Cpu &)> Cpu::addr_mode_rmw_ac(std::function<uint8_t(Cpu &, uint8_t)> instr) {
    return [&](Cpu &cpu) -> void {
        uint8_t result = instr(cpu, cpu.m_a);
        cpu.m_a = result;
    };
}

// zero page addressing mode wrapper for read-modify-write instructions
std::function<void(Cpu &)> Cpu::addr_mode_rmw_d(std::function<uint8_t(Cpu &, uint8_t)> instr) {
    return [&](Cpu cpu) -> void {
        uint8_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        uint8_t result = instr(cpu, cpu.m_bus.read_data(addr));
        cpu.m_bus.write_data(addr, result);
    };
};

// absolute addressing mode wrapper for read-modify-write instructions
std::function<void(Cpu &)> Cpu::addr_mode_rmw_a(std::function<uint8_t(Cpu &, uint8_t)> instr) {
    return [&](Cpu cpu) -> void {
        uint16_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr |= cpu.m_bus.read_data(cpu.m_pc++) << 8;
        uint8_t result = instr(cpu, cpu.m_bus.read_data(addr));
        cpu.m_bus.write_data(addr, result);
    };
};

// zero page x indexed addressing mode wrapper for read-modify-write instructions
std::function<void(Cpu &)> Cpu::addr_mode_rmw_dx(std::function<uint8_t(Cpu &, uint8_t)> instr) {
    return [&](Cpu cpu) -> void {
        uint8_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr += cpu.m_x;
        uint8_t result = instr(cpu, cpu.m_bus.read_data(addr));
        cpu.m_bus.write_data(addr, result);
    };
};

// absolute x indexed addressing mode wrapper for read-modify-write instructions
std::function<void(Cpu &)> Cpu::addr_mode_rmw_ax(std::function<uint8_t(Cpu &, uint8_t)> instr) {
    return [&](Cpu cpu) -> void {
        uint16_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr |= cpu.m_bus.read_data(cpu.m_pc++) << 8;
        addr += cpu.m_x;
        uint8_t result = instr(cpu, cpu.m_bus.read_data(addr));
        cpu.m_bus.write_data(addr, result);
    };
};

// zero page addressing mode wrapper for write instructions
std::function<void(Cpu &)> Cpu::addr_mode_w_d(std::function<uint8_t(Cpu &)> instr) {
    return [&](Cpu cpu) -> void {
        uint8_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        cpu.m_bus.write_data(addr, instr(cpu));
    };
}

// absolute addressing mode wrapper for write instructions
std::function<void(Cpu &)> Cpu::addr_mode_w_a(std::function<uint8_t(Cpu &)> instr) {
    return [&](Cpu cpu) -> void {
        uint16_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr |= cpu.m_bus.read_data(cpu.m_pc++) << 8;
        cpu.m_bus.write_data(addr, instr(cpu));
    };
}

// zero page x indexed addressing mode wrapper for write instructions
std::function<void(Cpu &)> Cpu::addr_mode_w_dx(std::function<uint8_t(Cpu &)> instr) {
    return [&](Cpu cpu) -> void {
        uint8_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr += cpu.m_x;
        cpu.m_bus.write_data(addr, instr(cpu));
    };
}

// zero page y indexed addressing mode wrapper for write instructions
std::function<void(Cpu &)> Cpu::addr_mode_w_dy(std::function<uint8_t(Cpu &)> instr) {
    return [&](Cpu cpu) -> void {
        uint8_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr += cpu.m_y;
        cpu.m_bus.write_data(addr, instr(cpu));
    };
}

// absolute x indexed addressing mode wrapper for write instructions
std::function<void(Cpu &)> Cpu::addr_mode_w_ax(std::function<uint8_t(Cpu &)> instr) {
    return [&](Cpu cpu) -> void {
        uint16_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr |= cpu.m_bus.read_data(cpu.m_pc++) << 8;
        addr += cpu.m_x;
        cpu.m_bus.write_data(addr, instr(cpu));
    };
}

// absolute y indexed addressing mode wrapper for write instructions
std::function<void(Cpu &)> Cpu::addr_mode_w_ay(std::function<uint8_t(Cpu &)> instr) {
    return [&](Cpu cpu) -> void {
        uint16_t addr = cpu.m_bus.read_data(cpu.m_pc++);
        addr |= cpu.m_bus.read_data(cpu.m_pc++) << 8;
        addr += cpu.m_y;
        cpu.m_bus.write_data(addr, instr(cpu));
    };
}

// indirect x indexed addressing mode wrapper for write instructions
std::function<void(Cpu &)> Cpu::addr_mode_w_ix(std::function<uint8_t(Cpu &)> instr) {
    return [&](Cpu cpu) -> void {

    };
}

// indirect y indexed addressing mode wrapper for write instructions
std::function<void(Cpu &)> Cpu::addr_mode_w_iy(std::function<uint8_t(Cpu &)> instr) {
    return [&](Cpu cpu) -> void {

    };
}

// add with carry
void Cpu::instr_adc(Cpu cpu, uint8_t arg) {
    uint16_t result = cpu.m_a + arg + cpu.m_flag_c;
    cpu.m_a = result;

    cpu.m_flag_c = result > 0xFF;
    cpu.m_flag_z = result == 0;
    cpu.m_flag_v = (result ^ cpu.m_a) & (result ^ arg) & 0x80;
    cpu.m_flag_n = cpu.m_a & 0x80;
}

// bitwise and
void Cpu::instr_and(Cpu cpu, uint8_t arg) {
    uint8_t result = cpu.m_a & arg;
    cpu.m_a = result;

    cpu.m_flag_z = result == 0;
    cpu.m_flag_n = result & 0x80;
}

// arithmetic shift left
uint8_t Cpu::instr_asl(Cpu cpu, uint8_t arg) {
    uint8_t result = arg < 1;

    cpu.m_flag_c = arg & 0x80;
    cpu.m_flag_z = result == 0;
    cpu.m_flag_n = result & 0x80;

    return result;
}

// branch if carry clear
void Cpu::instr_bcc(Cpu cpu) {
    int8_t arg = cpu.m_bus.read_data(cpu.m_pc++);
    if(!cpu.m_flag_c) {
        cpu.m_pc += arg;
    }
}

// branch if carry set
void Cpu::instr_bcs(Cpu cpu) {
    int8_t arg = cpu.m_bus.read_data(cpu.m_pc++);
    if(cpu.m_flag_c) {
        cpu.m_pc += arg;
    }
}

// branch if equal
void Cpu::instr_beq(Cpu cpu) {
    int8_t arg = cpu.m_bus.read_data(cpu.m_pc++);
    if(cpu.m_flag_z) {
        cpu.m_pc += arg;
    }
}

// bit test
void Cpu::instr_bit(Cpu cpu, uint8_t arg) {
    int8_t result = cpu.m_a & arg;
    cpu.m_flag_z = result == 0;
    cpu.m_flag_v = arg & 0x40;
    cpu.m_flag_n = arg & 0x80;
}

// branch if minus
void Cpu::instr_bmi(Cpu cpu) {
    int8_t arg = cpu.m_bus.read_data(cpu.m_pc++);
    if(cpu.m_flag_n) {
        cpu.m_pc += arg;
    }
}

// branch if not equal
void Cpu::instr_bne(Cpu cpu) {
    int8_t arg = cpu.m_bus.read_data(cpu.m_pc++);
    if(!cpu.m_flag_z) {
        cpu.m_pc += arg;
    }
}

// branch if plus
void Cpu::instr_bpl(Cpu cpu) {
    int8_t arg = cpu.m_bus.read_data(cpu.m_pc++);
    if(!cpu.m_flag_n) {
        cpu.m_pc += arg;
    }
}

// break (software IRQ)
void Cpu::instr_brk(Cpu cpu) {
    cpu.m_pc++;
    cpu.stack_push(cpu.m_pc >> 8);
    cpu.stack_push(cpu.m_pc);
    uint8_t ps = cpu.m_flag_n << 7 | cpu.m_flag_v << 6 | 1 << 5 | 1 << 4 |
        cpu.m_flag_d << 3 | cpu.m_flag_i << 2 | cpu.m_flag_z << 1 | cpu.m_flag_c << 0;
    cpu.stack_push(ps);
    cpu.m_pc = 0xFFFE;
}

// branch if overflow clear
void Cpu::instr_bvc(Cpu cpu) {
    int8_t arg = cpu.m_bus.read_data(cpu.m_pc++);
    if(!cpu.m_flag_v) {
        cpu.m_pc += arg;
    }
}

// branch if overflow set
void Cpu::instr_bvs(Cpu cpu) {
    int8_t arg = cpu.m_bus.read_data(cpu.m_pc++);
    if(cpu.m_flag_v) {
        cpu.m_pc += arg;
    }
}

// clear carry
void Cpu::instr_clc(Cpu cpu) {
    cpu.m_flag_c = false;
}

// clear decimal
void Cpu::instr_cld(Cpu cpu) {
    cpu.m_flag_d = false;
}

// clear interrupt disable
void Cpu::instr_cli(Cpu cpu) {
    cpu.m_flag_i = false;
}

// clear overflow
void Cpu::instr_clv(Cpu cpu) {
    cpu.m_flag_v = false;
}

// compare A
void Cpu::instr_cmp(Cpu cpu, uint8_t arg) {
    uint8_t result = cpu.m_a - arg;

    cpu.m_flag_c = cpu.m_a > arg;
    cpu.m_flag_z = cpu.m_a == arg;
    cpu.m_flag_n = result & 0x80;
}

// compare X
void Cpu::instr_cpx(Cpu cpu, uint8_t arg) {
    uint8_t result = cpu.m_x - arg;

    cpu.m_flag_c = cpu.m_x > arg;
    cpu.m_flag_z = cpu.m_x == arg;
    cpu.m_flag_n = result & 0x80;
}

// compare Y
void Cpu::instr_cpy(Cpu cpu, uint8_t arg) {
    uint8_t result = cpu.m_y - arg;

    cpu.m_flag_c = cpu.m_y > arg;
    cpu.m_flag_z = cpu.m_y == arg;
    cpu.m_flag_n = result & 0x80;
}

// decrement memory
uint8_t Cpu::instr_dec(Cpu cpu, uint8_t arg) {
    return arg - 1;
}

// decrement X
void Cpu::instr_dex(Cpu cpu) {
    cpu.m_x--;
}

// decrement Y
void Cpu::instr_dey(Cpu cpu) {
    cpu.m_y--;
}

// bitwise exclusive or
void Cpu::instr_eor(Cpu cpu, uint8_t arg) {
    cpu.m_a = cpu.m_a ^ arg;
}

// increment memory
uint8_t Cpu::instr_inc(Cpu cpu, uint8_t arg) {
    return arg + 1;
}

// increment x
void Cpu::instr_inx(Cpu cpu) {
    cpu.m_x++;
}

// increment y
void Cpu::instr_iny(Cpu cpu) {
    cpu.m_y++;
}

// jump
void Cpu::instr_jmp(Cpu cpu, uint8_t arg) {
    cpu.m_pc = arg;
}

// jump to subroutine
void Cpu::instr_jsr(Cpu cpu, uint8_t arg) {
    cpu.m_pc++;
    cpu.stack_push(cpu.m_pc >> 8);
    cpu.stack_push(cpu.m_pc);
    cpu.m_pc = arg;
}

// load A
void Cpu::instr_lda(Cpu cpu, uint8_t arg) {
    cpu.m_a = arg;
}

// load X
void Cpu::instr_ldx(Cpu cpu, uint8_t arg) {
    cpu.m_x = arg;
}

// load Y
void Cpu::instr_ldy(Cpu cpu, uint8_t arg) {
    cpu.m_y = arg;
}


// logical shift right
uint8_t Cpu::instr_lsr(Cpu cpu, uint8_t arg) {
    cpu.m_flag_c = arg & 0x01;

    return arg >> 1;
}


// no operation
void Cpu::instr_nop(Cpu cpu) {

}

// bitwise or
void Cpu::instr_ora(Cpu cpu, uint8_t arg) {
    cpu.m_a |= arg;
}

// push A
void Cpu::instr_pha(Cpu cpu) {
    cpu.stack_push(cpu.m_a);
}

// push processor status
void Cpu::instr_php(Cpu cpu) {
    uint8_t ps = cpu.m_flag_n << 7 | cpu.m_flag_v << 6 | 1 << 5 | 1 << 4 |
        cpu.m_flag_d << 3 | cpu.m_flag_i << 2 | cpu.m_flag_z << 1 | cpu.m_flag_c << 0;
    cpu.stack_push(ps);
}

// pull A
void Cpu::instr_pla(Cpu cpu) {
    cpu.m_a = cpu.stack_pull();
}

// pull processor status
void Cpu::instr_plp(Cpu cpu) {
    uint8_t ps = cpu.stack_pull();

    cpu.m_flag_n = ps & 0x80;
    cpu.m_flag_v = ps & 0x40;
    cpu.m_flag_d = ps & 0x08;
    cpu.m_flag_i = ps & 0x04;
    cpu.m_flag_z = ps & 0x02;
    cpu.m_flag_c = ps & 0x01;
}

// rotate left
uint8_t Cpu::instr_rol(Cpu cpu, uint8_t arg) {
    uint16_t result = arg << 1;
    result |= cpu.m_flag_c;
    cpu.m_flag_c = result & 0x10;
    
    return result;
}

// rotate right
uint8_t Cpu::instr_ror(Cpu cpu, uint8_t arg) {
    uint16_t result = arg;
    result |= cpu.m_flag_c << 8;
    cpu.m_flag_c = result & 0x01;
    
    return result >> 1;
}

// return from interrut
void Cpu::instr_rti(Cpu cpu) {
    uint8_t ps = cpu.stack_pull();
    uint16_t pc = cpu.stack_pull();
    pc |= cpu.stack_pull() << 8;
    cpu.m_pc = pc;

    cpu.m_flag_n = ps & 0x80;
    cpu.m_flag_v = ps & 0x40;
    cpu.m_flag_d = ps & 0x08;
    cpu.m_flag_i = ps & 0x04;
    cpu.m_flag_z = ps & 0x02;
    cpu.m_flag_c = ps & 0x01;
}

// return from subroutine
void Cpu::instr_rts(Cpu cpu) {
    uint16_t pc = cpu.stack_pull();
    pc |= cpu.stack_pull() << 8;
    cpu.m_pc = pc + 1;
}

// subtract with carry
void Cpu::instr_sbc(Cpu cpu, uint8_t arg) {
    uint16_t result = cpu.m_a - arg - !cpu.m_flag_c;

    cpu.m_flag_c = ~(result > 0xFF);
    cpu.m_flag_z = result == 0;
    cpu.m_flag_v = (result ^ cpu.m_a) & (result ^ ~arg) & 0x80;
}

// set carry
void Cpu::instr_sec(Cpu cpu) {
    cpu.m_flag_c = true;
}

// set decimal
void Cpu::instr_sed(Cpu cpu) {
    cpu.m_flag_d = true;
}

// set interrupt disable
void Cpu::instr_sei(Cpu cpu) {
    cpu.m_flag_i = true;
}

// store A
uint8_t Cpu::instr_sta(Cpu cpu) {
    return cpu.m_a;
}

// store X
uint8_t Cpu::instr_stx(Cpu cpu) {
    return cpu.m_x;
}

// store Y
uint8_t Cpu::instr_sty(Cpu cpu) {
    return cpu.m_y;
}

// transfer A to X
void Cpu::instr_tax(Cpu cpu) {
    cpu.m_x = cpu.m_a;
}

// transfer A to Y
void Cpu::instr_tay(Cpu cpu) {
    cpu.m_y = cpu.m_a;
}

// transfer stack pointer to X
void Cpu::instr_tsx(Cpu cpu) {
    cpu.m_x = cpu.m_s;
}

// transfer X to A
void Cpu::instr_txa(Cpu cpu) {
    cpu.m_a = cpu.m_x;
}

// tranfer X to stack pointer
void Cpu::instr_txs(Cpu cpu) {
    cpu.m_s = cpu.m_x;
}

// transfer Y to A
void Cpu::instr_tya(Cpu cpu) {
    cpu.m_a = cpu.m_y;
}
