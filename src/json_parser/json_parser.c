#include "mpc.h"
#include <editline/readline.h>

int main ( int argc, char ** argv) {
	mpc_parser_t* Json    = mpc_new("json");
	mpc_parser_t* Object  = mpc_new("object");
	mpc_parser_t* Array   = mpc_new("array");
	mpc_parser_t* Item    = mpc_new("item");
	mpc_parser_t* Map     = mpc_new("map");
	mpc_parser_t* Value   = mpc_new("value");
	mpc_parser_t* Number  = mpc_new("number");
	mpc_parser_t* String  = mpc_new("string");
	mpc_parser_t* Boolean = mpc_new("boolean");
 	
	mpca_lang(MPCA_LANG_DEFAULT,
		" "                                                    
		"    boolean : /true|false/ ;                       " 
		"    number  : /-?[0-9]+/ ;                                 " 
		"    string  : /\"[A-Za-z0-9]*\"/ ;                       " 
		"    value   : <string> | <number> | <boolean> ;            " 
		"    item    : <object> | <array> ;                         " 
		"    map     : <string> ':' ( <object> | <array>) ;                         " 
		"    array   : '[' <item> ( ',' <item> ) * ']' ;            "   
		"    object  : ( '{' <map> ( ','<map> )* '}' ) | <value> ;" 
		"    json    : /^/ <object> | <array> /$/ ;                                " 
	    " ",
	    Boolean,Number,String,Value,Item,Map,Array,Object,Json);	
    while (1) {
	  
	    char* input = readline("json > ");
		add_history(input);
		    
		/* Attempt to parse the user input */
		mpc_result_t r;
		if (mpc_parse("<stdin>", input, Json, &r)) {
		      /* On success print and delete the AST */
		      mpc_ast_print(r.output);
			  mpc_ast_delete(r.output);
        } else {
         	/* Otherwise print and delete the Error */
		    mpc_err_print(r.error);
		    mpc_err_delete(r.error);
	   }
	   free(input);
	}
	mpc_cleanup(7,Json,Object,Array,Item,Number,String,Boolean);	

	return 0;
}

