#include "mpc.h"
#include "lispq_common.h"
void line_parser(mpc_parser_t * root, char * input) {
		mpc_result_t r;
				
		if (mpc_parse("<stdin>", input, root, &r)) {
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);
		} else {
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
}
int main(int argc, char ** argv) {
	lispq_init();
	lispq_handler(line_parser);
	lispq_cleanup();
	return 0;
}
