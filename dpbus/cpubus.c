#include "em_int.h"

#include "cpubus.h"
#include "dpbus.h"

void fpga_set_state(cpu_bus_t *cpu_bus, fpga_state_t state) {
    switch(state) {
        case RUN:
            set_bus_state(&cpu_bus->addr_bus, BUS_INPUT_HIGH_IMPEDANCE);
            set_bus_state(&cpu_bus->data_bus, BUS_INPUT_HIGH_IMPEDANCE);

            set_data(&cpu_bus->cpu_enable, 1);
            set_data(&cpu_bus->chip_enable, 1);
            set_data(&cpu_bus->write_enable, 1);
            set_data(&cpu_bus->cpu_state, 0);
            set_data(&cpu_bus->LBUB, 1);
            /*set_bus_state(&cpu_bus->chip_enable, BUS_OUTPUT); Not needed */
            /*set_bus_state(&cpu_bus->cpu_enable, BUS_OUTPUT); Not needed */
            /*set_bus_state(&cpu_bus->write_enable, BUS_OUTPUT); Not needed */
            /*set_bus_state(&cpu_bus->cpu_state, BUS_OUTPUT); Not needed */
            /*set_bus_state(&cpu_bus->LBUB, BUS_OUTPUT); Not needed */
            break;
        case INSTRUCTION_LOW_ACCESS:
            set_bus_state(&cpu_bus->addr_bus, BUS_OUTPUT);
            set_bus_state(&cpu_bus->data_bus, BUS_INPUT_HIGH_IMPEDANCE);

            set_data(&cpu_bus->cpu_enable, 0);
            /* TODO Wait a few cycles */
            set_data(&cpu_bus->chip_enable, 1);
            set_data(&cpu_bus->write_enable, 1);
            set_data(&cpu_bus->cpu_state, 2);
            set_data(&cpu_bus->LBUB, 0);
            break;
        case INSTRUCTION_HIGH_ACCESS:
            set_bus_state(&cpu_bus->addr_bus, BUS_OUTPUT);
            set_bus_state(&cpu_bus->data_bus, BUS_INPUT_HIGH_IMPEDANCE);

            set_data(&cpu_bus->cpu_enable, 0);
            /* TODO Wait a few cycles */
            set_data(&cpu_bus->chip_enable, 1);
            set_data(&cpu_bus->write_enable, 1);
            set_data(&cpu_bus->cpu_state, 1);
            set_data(&cpu_bus->LBUB, 0);
            break;
        case DATA_ACCESS:
            set_bus_state(&cpu_bus->addr_bus, BUS_OUTPUT);
            set_bus_state(&cpu_bus->data_bus, BUS_INPUT_HIGH_IMPEDANCE);

            set_data(&cpu_bus->cpu_enable, 0);
            /* TODO Wait a few cycles */
            set_data(&cpu_bus->chip_enable, 1);
            set_data(&cpu_bus->write_enable, 1);
            set_data(&cpu_bus->cpu_state, 3);
            set_data(&cpu_bus->LBUB, 0);
            break;
    }
}

void set_cpu_memory(cpu_bus_t *cpu_bus, uint32_t address, unsigned int data) {
    /* Disable interrupts while writing to memory */
    INT_Disable();

    set_data(&cpu_bus->addr_bus, address);
    set_data(&cpu_bus->chip_enable, 0);
    set_data(&cpu_bus->write_enable, 0);
    /* Wait? */

    set_bus_state(&cpu_bus->data_bus, BUS_OUTPUT);
    set_data(&cpu_bus->data_bus, data);
    /* Wait? */

    set_data(&cpu_bus->write_enable, 1);
    set_data(&cpu_bus->chip_enable, 1);
    set_bus_state(&cpu_bus->data_bus, BUS_INPUT_HIGH_IMPEDANCE);

    /* Enable interrupts again */
    INT_Enable();
}

unsigned int read_cpu_memory(cpu_bus_t *cpu_bus, uint32_t address) {
    /* Disable interrupts while reading from memory */
    INT_Disable();

    set_data(&cpu_bus->addr_bus, address);
    /* Wait? */
    set_data(&cpu_bus->chip_enable, 0);
    /*set_bus_state(&cpu_bus->data_bus, BUS_INPUT_PULLDOWN); Not needed ? */
    /* Must wait at least 10ns */
    int result = read_data(&cpu_bus->data_bus);

    set_data(&cpu_bus->chip_enable, 1);

    /* Enable interrupts again */
    INT_Enable();

    return result;
}
