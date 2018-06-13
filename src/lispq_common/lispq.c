#include "mpc.h"
#include <editline/readline.h>
#include "lispq_common.h"

mpc_parser_t* Number   ;
mpc_parser_t* Operator ;
mpc_parser_t* Expr     ;
mpc_parser_t* Lispq    ;

void lispq_init() {
	Number    = mpc_new("number");
	Operator  = mpc_new("operator");
	Expr      = mpc_new("expr");
	Lispq     = mpc_new("lispq");
	mpca_lang(MPCA_LANG_DEFAULT,
			" "
			" number   : /-?[0-9]+/ ;                            "
			" operator : '+' | '-' | '*' | '/' ;                 " 
			" expr     : <number> | '(' <operator> <expr>+ ')' ; "
			" lispq    : /^/ <operator> <expr>+ /$/ ;            "
			, Number, Operator, Expr, Lispq);

}
void lispq_handler(f handler) {

	puts("Lispq Version 0.0.1");
	puts("Press ctl-c to Exit\n");

	while (1) {
		char * input = readline("lispq > ");
		add_history(input);

		handler(Lispq,input);

		free(input);
	}

	lisp_cleanup();
	return 0;
}
void lispq_cleanup() {
	mpc_cleanup(4, Number, Operator, Expr, Lispq);
}
