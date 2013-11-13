#include <stdio.h>
#include "dpbus.h"
#include "cpubus.h"

int main() {
    line_t addr_line[19] = {
               PORT(C, 0),
               PORT(C, 1),
               PORT(C, 2),
               PORT(C, 3),
               PORT(C, 4),
               PORT(C, 5),
               PORT(C, 6),
               PORT(C, 7),
               PORT(C, 8),
               PORT(C, 9),
               PORT(C, 10),
               PORT(C, 11),
               PORT(E, 0),
               PORT(E, 1),
               PORT(E, 2),
               PORT(E, 3),
               PORT(E, 4),
               PORT(E, 5),
               PORT(E, 6)
           },
           data_line[16] = {
               PORT(A, 0),
               PORT(A, 1),
               PORT(A, 2),
               PORT(A, 3),
               PORT(A, 4),
               PORT(A, 5),
               PORT(A, 6),
               PORT(A, 7),
               PORT(A, 8),
               PORT(A, 9),
               PORT(A, 10),
               PORT(A, 11),
               PORT(A, 12),
               PORT(A, 13),
               PORT(A, 14),
               PORT(A, 15),
           },
           chip_enable_line[1] = {PORT(E, 9)},
           cpu_enable_line[1] = {PORT(D, 15)},
           write_enable_line[1] = {PORT(E, 8)},
           cpu_state_line[2] = {
               PORT(D, 13),
               PORT(D, 14)
           },
           LBUB_line[1] = {PORT(E, 7)};

    cpu_bus_t cpu_bus = {
        initialise_bus(19, addr_line, BUS_INPUT_HIGH_IMPEDANCE),
        initialise_bus(16, data_line, BUS_INPUT_HIGH_IMPEDANCE),
        initialise_bus(1, chip_enable_line, BUS_OUTPUT),
        initialise_bus(1, cpu_enable_line, BUS_OUTPUT),
        initialise_bus(1, write_enable_line, BUS_OUTPUT),
        initialise_bus(2, cpu_state_line, BUS_OUTPUT),
        initialise_bus(1, LBUB_line, BUS_OUTPUT)
    };

    unsigned int result[4];

    fpga_set_state(&cpu_bus, DATA_ACCESS);

    set_cpu_memory(&cpu_bus, 0x1, 0x1);
    set_cpu_memory(&cpu_bus, 0x5, 0x1);
    set_cpu_memory(&cpu_bus, 0x9, 0x1);
    set_cpu_memory(&cpu_bus, 0xd, 0x1);

    fpga_set_state(&cpu_bus, INSTRUCTION_LOW_ACCESS);
    /* Assumed least significant bits */

    set_cpu_memory(&cpu_bus, 0x1, 0x0006);
    set_cpu_memory(&cpu_bus, 0x2, 0x0008);
    set_cpu_memory(&cpu_bus, 0x3, 0x000A);
    set_cpu_memory(&cpu_bus, 0x4, 0x000C);
    set_cpu_memory(&cpu_bus, 0x5, 0x0010);
    set_cpu_memory(&cpu_bus, 0x6, 0x000D);
    set_cpu_memory(&cpu_bus, 0x7, 0x0050);
    set_cpu_memory(&cpu_bus, 0x8, 0x000D);
    set_cpu_memory(&cpu_bus, 0x9, 0x0090);
    set_cpu_memory(&cpu_bus, 0xa, 0x000D);
    set_cpu_memory(&cpu_bus, 0xb, 0x00D0);
    set_cpu_memory(&cpu_bus, 0xc, 0x4000);
    set_cpu_memory(&cpu_bus, 0xd, 0x8010);
    set_cpu_memory(&cpu_bus, 0xe, 0x4000);
    set_cpu_memory(&cpu_bus, 0xf, 0x0011);

    fpga_set_state(&cpu_bus, INSTRUCTION_HIGH_ACCESS);
    /* Assumed most significant bits */

    set_cpu_memory(&cpu_bus, 0x1, 0xF200);
    set_cpu_memory(&cpu_bus, 0x2, 0xF200);
    set_cpu_memory(&cpu_bus, 0x3, 0xF200);
    set_cpu_memory(&cpu_bus, 0x4, 0xF200);
    set_cpu_memory(&cpu_bus, 0x5, 0xFC08);
    set_cpu_memory(&cpu_bus, 0x6, 0xF200);
    set_cpu_memory(&cpu_bus, 0x7, 0xFC08);
    set_cpu_memory(&cpu_bus, 0x8, 0xF200);
    set_cpu_memory(&cpu_bus, 0x9, 0xFC08);
    set_cpu_memory(&cpu_bus, 0xa, 0xF200);
    set_cpu_memory(&cpu_bus, 0xb, 0xFC08);
    set_cpu_memory(&cpu_bus, 0xc, 0xF010);
    set_cpu_memory(&cpu_bus, 0xd, 0xFC10);
    set_cpu_memory(&cpu_bus, 0xe, 0xF110);
    set_cpu_memory(&cpu_bus, 0xf, 0xF200);

    fpga_set_state(&cpu_bus, RUN);
    /* Be sure not to optimise this out */
    for(int i = 0; i < 32000000; i++);

    fpga_set_state(&cpu_bus, DATA_ACCESS);

    result[0] = read_cpu_memory(&cpu_bus, 0x1);
    result[1] = read_cpu_memory(&cpu_bus, 0x5);
    result[2] = read_cpu_memory(&cpu_bus, 0x9);
    result[2] = read_cpu_memory(&cpu_bus, 0xd);

    printf("Value stored at 0x1: 0x%x\n", result[0]);
    printf("Value stored at 0x5: 0x%x\n", result[1]);
    printf("Value stored at 0x9: 0x%x\n", result[2]);
    printf("Value stored at 0xd: 0x%x\n", result[3]);
    return 0;
}
