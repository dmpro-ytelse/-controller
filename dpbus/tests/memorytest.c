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

    unsigned int result;

    fpga_set_state(&cpu_bus, DATA_ACCESS);

    printf("Writing 0xf0 to 0x1 in data memory\n");

    set_cpu_memory(&cpu_bus, 0x1, 0xf0);

    result = read_cpu_memory(&cpu_bus, 0x1);

    printf("Value stored at 0x1: 0x%x\n", result);

    fpga_set_state(&cpu_bus, INSTRUCTION_LOW_ACCESS);

    printf("Writing 0xf0 to 0x1 in low instruction memory\n");

    set_cpu_memory(&cpu_bus, 0x1, 0xf0);

    result = read_cpu_memory(&cpu_bus, 0x1);

    printf("Value stored at 0x1: 0x%x\n", result);

    fpga_set_state(&cpu_bus, INSTRUCTION_HIGH_ACCESS);

    printf("Writing 0xf0 to 0x1 in high instruction memory\n");

    set_cpu_memory(&cpu_bus, 0x1, 0xf0);

    result = read_cpu_memory(&cpu_bus, 0x1);

    printf("Value stored at 0x1: 0x%x\n", result);
    return 0;
}
