#include "mpc.h"
#include "lispq_common.h"

long eval_op(long x, char * op, long y) {
	switch (op[0]){
		case '+': return x + y ;
		case '-': return x - y ;
		case '*': return x * y ;
		case '/': return x / y ;
	}
	return 0;
}

long eval(mpc_ast_t * t) {
	
	if (strstr(t->tag, "number")) {
		return atoi(t->contents);
	}

	char * op = t->children[1]->contents;

	long x = eval(t->children[2]);

	int index = 3;
	while (strstr(t->children[index]->tag, "expr")) {
		x = eval_op(x, op, eval(t->children[index]));
		index += 1;
	}
	return x;
}

void eval_handler(mpc_parser_t * root, char * input) {
		mpc_result_t r;
				
		if (mpc_parse("<stdin>", input, root, &r)) {
			long result = eval(r.output);
			printf("%li\n", result);
			mpc_ast_delete(r.output);
		} else {
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
}
int main(int argc, char ** argv) {
	lispq_init();
	lispq_handler(eval_handler);
	lispq_cleanup();
	return 0;
}
