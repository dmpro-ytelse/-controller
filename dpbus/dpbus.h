#ifndef DPBUS_H_
#define DPBUS_H_

#include "em_gpio.h"

#define PORT(port, pin) {gpioPort ## port, pin}

/* TODO REMOVE this */
typedef int GPIO_Mode_TypeDef;
typedef int GPIO_Port_TypeDef;
#define gpioModeInputPull 1
#define gpioModePushPull 2
GPIO_PinModeSet(GPIO_Port_TypeDef, unsigned int, GPIO_Mode_TypeDef, unsigned int);
#define EFM_ASSERT(expr) ((void)0);
/* STOP TODO */

typedef struct {
    GPIO_Port_TypeDef port;
    unsigned int pin;
} line_t;

typedef enum {BUS_INPUT_PULLUP, BUS_INPUT_PULLDOWN, BUS_OUTPUT} bus_state_t;

/* Input/output_mode left in case we want to configure them later */
typedef struct {
    int size;
    line_t *lines;
    bus_state_t state;

    GPIO_Mode_TypeDef input_mode;
    GPIO_Mode_TypeDef output_mode;
} bus_t;

bus_t initialise_bus(int size, line_t *lines, bus_state_t state);
void set_data(bus_t *bus, unsigned int value);
unsigned int read_data(bus_t *bus);
void set_bus_state(bus_t *bus, bus_state_t state);

#endif
