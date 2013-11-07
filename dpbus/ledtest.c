#include "dpbus.h"

int main() {
    line_t in_lines[2] = {
               PORT(A, 0),
               PORT(A, 1)
          },
          out_lines[2] = {
               PORT(A, 2),
               PORT(A, 3)
          };

    bus_t in_bus = initialise_bus(2, in_lines, BUS_INPUT_PULLUP),
          out_bus = initialise_bus(2, out_lines, BUS_OUTPUT);

    int input = 0;
    while (input != 3) {
        input = read_data(&in_bus);
        set_data(&out_bus, input);
    }

    set_bus_state(&in_bus, BUS_OUTPUT);
    set_bus_state(&out_bus, BUS_INPUT_PULLUP);

    input = 0;
    while (input != 3) {
        input = read_data(&out_bus);
        set_data(&in_bus, input);
    }

    set_bus_state(&out_bus, BUS_OUTPUT);

    set_data(&out_bus, 3);

    return 0;
}
