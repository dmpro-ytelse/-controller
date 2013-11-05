#include "em_assert.h"
#include "em_gpio.h"
#include "dpbus.h"

bus_t initialise_bus(int size, line_t *lines, bus_state_t state) {
    bus_t bus = {
        size,
        lines,
        state,
        gpioModeInputPull,
        gpioModeInput,
        gpioModePushPull
    };

    set_bus_state(&bus, state);

    return bus;
}

void set_data(bus_t *bus, unsigned int value) {
    EFM_ASSERT(bus->state == BUS_OUTPUT);

    for (int i = 0, j = 1; i < bus->size; i++, j <<= 1) {
        if (value & j) {
            GPIO_PinOutSet(bus->lines[i].port, bus->lines[i].pin);
        } else {
            GPIO_PinOutClear(bus->lines[i].port, bus->lines[i].pin);
        }
    }
}

static unsigned int get_ports_value(bus_t *bus) {
    unsigned int result = 0;

    for (int i = 0; i < bus->size; i++) {
        result |= (!!GPIO_PinInGet(bus->lines[i].port, bus->lines[i].pin)) << i;
    }

    return result;
}

unsigned int read_data(bus_t *bus) {
    EFM_ASSERT(bus->state != BUS_OUTPUT);

    unsigned int result = get_ports_value(bus),
                 tmp;
    int unstable = 1;

    /* Wait until data has been stable n times so that we're sure it's stable */
    while(unstable) {
        unstable = 0;

        for (int i = 0; i < 10; i++) {
            tmp = get_ports_value(bus);
            if (tmp != result) {
                result = tmp;
                unstable = 1;
                break;
            }
        }
    }

    return result;
}

void set_bus_state(bus_t *bus, bus_state_t state) {
    GPIO_Mode_TypeDef mode;
    if (state == BUS_OUTPUT) {
        mode = bus->output_mode;
    } else if (state == BUS_INPUT_HIGH_IMPEDANCE) {
        mode = bus->input_impedance_mode;
    } else {
        mode = bus->input_pull_mode;
    }

    int output_value = state == BUS_INPUT_PULLUP;

    for (int i = 0; i < bus->size; i++) {
        GPIO_PinModeSet(bus->lines[i].port, bus->lines[i].pin, mode, output_value);
    }

    bus->state = state;
}
