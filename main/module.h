#ifndef MODULE_H_
#define MODULE_H_

#define MAX_MODULES 16

typedef struct {
    int module;
    void *data;
} event_t;

typedef struct {
    int module;
    /* Should return a pointer to the event data or NULL for no event */
    void *(*poll_module)();
    void (*handle_event)(event_t);
} module_t;

module_t *new_module(void *(*poll_module)(), void (*handle_event)(event_t));
void main_loop();

#endif
