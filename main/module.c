#include <stdlib.h>

#include "module.h"

module_t modules[MAX_MODULES];
int n_modules = 0;

module_t *new_module(void *(*poll_module)(), void (*handle_event)(event_t)) {
    modules[n_modules] = (module_t){n_modules, poll_module, handle_event};
    return &modules[n_modules++];
}

void main_loop() {
    void *tmp;

    while (1) {
        for (int i = 0; i < n_modules; i++) {
            tmp = modules[i].poll_module();
            if (tmp != NULL) {
                for (int n = 0; n < n_modules; n++) {
                    modules[n].handle_event((event_t) {i, tmp});
                }
            }
        }
    }
}
