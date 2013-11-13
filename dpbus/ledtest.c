#include "dpbus.h"

int main() {
    line_t in_lines[8] = {
               PORT(B, 0),
               PORT(B, 1),
               PORT(B, 2),
               PORT(B, 3),
               PORT(B, 4),
               PORT(B, 5),
               PORT(B, 6),
               PORT(B, 7)
          },
          out_lines[16] = {
               PORT(B, 8),
               PORT(B, 11),
               PORT(B, 12),
               PORT(B, 15),
               PORT(D, 0),
               PORT(D, 2),
               PORT(D, 3),
               PORT(D, 4),
               PORT(D, 5),
               PORT(D, 6),
               PORT(D, 7),
               PORT(D, 8),
               PORT(D, 9),
               PORT(D, 10),
               PORT(D, 11),
               PORT(D, 12)
          };

    bus_t in_bus = initialise_bus(8, in_lines, BUS_INPUT_PULLUP),
          out_bus = initialise_bus(16, out_lines, BUS_OUTPUT);

    int input = 0, output;
    while (1) {
        input = read_data(&in_bus);

        output = 0;
        for (int i = 1, j = 3; i < (1 << 8); i <<= 1, j <<= 1) {
            if (input & i) {
                output |= j;
            }
        }

        set_data(&out_bus, output);
    }

    return 0;
}
