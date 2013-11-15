#ifndef CPUBUS_H_
#define CPUBUS_H_

#include <stdint.h>

#include "dpbus.h"

typedef struct {
    bus_t addr_bus;
    bus_t data_bus;
    bus_t chip_enable;
    bus_t cpu_enable;
    bus_t write_enable;
    bus_t cpu_state;
    bus_t LBUB;
} cpu_bus_t;

typedef enum {RUN, INSTRUCTION_LOW_ACCESS, INSTRUCTION_HIGH_ACCESS, DATA_ACCESS} fpga_state_t;

typedef uint8_t byte;

void fpga_set_state(cpu_bus_t *cpu_bus, fpga_state_t state);
void set_cpu_memory(cpu_bus_t *cpu_bus, uint32_t address, unsigned int data);
unsigned int read_cpu_memory(cpu_bus_t *cpu_bus, uint32_t address);

#endif
