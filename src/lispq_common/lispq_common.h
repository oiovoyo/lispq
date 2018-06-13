#include "mpc.h"

typedef void (*f)(mpc_parser_t * root, char * line);
void lispq_init();
void lispq_handler(f);
void lispq_cleanup();
