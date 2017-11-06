/**<parser.c>::**/
#include <stdio.h>
#include <stdlib.h>
#include <gettoken.h>
#include <parser.h>
#include <string.h>
#include <keywords.h>
#include <symtab.h>
#include <macros.h>

/** lexer-parser interface **/
int lookahead;

void match(int expected) {
	if (lookahead == expected) {
		lookahead = gettoken(src);
	} else {
		if (expected >= BEGIN) {
			if (lookahead >= BEGIN) {
				fprintf(stderr, "token mismatch: expected '%s' whereas found '%s'\n", printkeyword(expected), printkeyword(lookahead));
			} else {
				fprintf(stderr, "token mismatch: expected '%s' whereas found '%c'\n", printkeyword(expected), lookahead);
			}
		} else {
			if (lookahead >= BEGIN) {
				fprintf(stderr, "token mismatch: expected '%c' whereas found '%s'\n", expected, printkeyword(lookahead));
			} else {
				fprintf(stderr, "token mismatch: expected '%c' whereas found '%c'\n", expected, lookahead);
			}
		}
		exit(-3);
	}
}

/** syntax definitions **/

/*
  LL(1)- EBNF proto-pascal mutant

   mypas --> declarative imperative '.'
*/

void mypas (void) {
	declaratives();
	imperatives();
	match('.');
}

/* declaratives --> VAR varlist ':' vartype ';' {varlist ':' vartype ';'} */

void declaratives (void) {
	/**/ int init, grptype; /**/
	match(VAR);
	VAR_START:
		/**/ init = /**/ varlist();
		match(':');
		/**/ grptype = /**/ vartype();
		match(';');
		/**/ symtab_settype(grptype, init); /**/
		
		if(lookahead == ID) {
			goto VAR_START;
		}
}

/* imperatives --> BEGIN stmtlist END */

void imperatives(void) {
	match(BEGIN);
	stmtlist();
	match(END);
}

/* varlist --> ID { ',' ID } */

int varlist(void) {
	/**/ int symtab_first = symtab_nextentry; /**/
	VARLIST:
		/**/
		if (symtab_append(lexeme) == 0) {
			fprintf(stderr, "%s already declared\n", lexeme);
		}
		/**/
		match(ID);
		if (lookahead == ',') {
			match(',');
			goto VARLIST;
		}
	return symtab_first;	
}

/* vartype --> BYTE | WORD | INTEGER | REAL | DOUBLE | BOOLEAN | CHAR | STRING */

int vartype(void) {
	/**/ int typeindex = str, typetotal = str; /**/
	switch (lookahead) {
		case BYTE:
			typeindex--;
		case WORD:
			typeindex--;
		case INTEGER:
			typeindex--;
		case REAL:
			typeindex--;
		case DOUBLE:
			typeindex--;
		case BOOLEAN:
			typeindex--;
		case CHAR:
			typeindex--;
			match (lookahead);
			return typeindex;
		default:
			match (STRING);
			return typetotal;
	}
}

/* expr --> E [ otilde E ]*/

int expr(int inherited_type) {
	/**/ int otilde, left_expr_type, right_expr_type; /**/
	/**/ left_expr_type = /**/ E(0);
	if (otilde = isotilde()) {				// caso relacional
		match(otilde);
		/**/ right_expr_type = /**/ E(0);
		/**/
		if (typeclass(left_expr_type) == typeclass(right_expr_type)) {
			return boolean;
		}
		fprintf(stderr, "left operand is incompatible to right operand\n");
		return 0;
		/**/
	}
	/**/
	if (inherited_type == 0) {
		return left_expr_type;
	}
	if (typeclass(inherited_type) == typeclass(left_expr_type)) {
		return max(inherited_type, left_expr_type);
	}
	/**/
	fprintf(stderr, "expression type is in invalidy context\n");
	return 0;
}

/* stmt --> expr */

void stmt(void){
	switch (lookahead) {
		case BEGIN:
			imperatives();
			break;
		case IF:
			match(IF);
			expr(/**/boolean/**/);
			match(THEN);
			stmt();
			if (lookahead == ELSE) {
				match(ELSE);
				stmt();
			}
			break;
		case WHILE:
			match(WHILE);
			expr(/**/boolean/**/);
			match(DO);
			stmt();
			break;
		case REPEAT:
			match(REPEAT);
			stmtlist();
			match(UNTIL);
			expr(/**/boolean/**/);
			break;
		case ID:
			E(0);
			break;
		default:
		   ;
	}
}

/* stmtlist --> stmt { ';' stmt } */

void stmtlist(void) {
	STMTLIST:
		stmt();
		if (lookahead == ';') {
			match(';');
			goto STMTLIST;
		}
}

/* oplus --> "+" | "-" | OR */

int isoplus(void){
	switch (lookahead){
	case '+':
	case '-':
    	return lookahead;
	}
	return 0;
}

/* negate --> "-" | NOT */

int isnegate(void) {
	switch (lookahead) {
		case '-':
		case NOT:
			return lookahead;
	}
	return 0;
}

/* otimes --> "*" | "/" | DIV | MOD | AND */

int isotimes(void){
	switch (lookahead) {
  		case '*':
  		case '/':
  		//case DIV:
  		//case MOD:
  		//case AND:
    		return lookahead;
	}
	return 0;
}

/* otilde --> "=" | ">" | ">=" | "<" | "<=" | "<>" */

int isotilde(void) {
	switch (lookahead) {
		case '=':
		case '<':
		case '>':
		case NEQ:
		case LEQ:
		case GEQ:
			return lookahead;
	}
	return 0;
}

/* E --> [ ominus ] T {oplus T} */

int E (int inherited_type) {

	/**/int negate, acctype, type;/**/

E_start:
	if (negate = isnegate()) {
 		match(negate);
 	}

/* T --> F {otimes F} */	
T_start:
/* F --> num | var | (E) */
F_start:
    switch (lookahead) {
		case DEC:
		case FLT:
		 	match(lookahead);
		 	break; 	
		case ID:
			match(ID);
			if (lookahead == ASGNM) {
				match(ASGNM); 
				E(0);
			} else {
				;	
			}
			break;
		default:
			match('('); E(0/*rever esse 0*/); match(')');
	}

F_end:
	if (isotimes()) {
		match(lookahead);
		goto F_start;
  	}

T_end:
	if(isoplus()){
		match(lookahead);
		goto T_start;
	}

E_end:
	; 
}

/* FIRST (E) = set( '(', num, var ) */

int isFIRST_E (void){
	switch (lookahead){
		case '(': 
		case DEC: 
		case FLT:
		case ID: 
		//ADICIONAR AS CONSTANTES STRING, BOOLEAN, ETC, MAS POR ENQUANTO USAR SÓ NUMEROS
		return lookahead;
		case ';':
			return 0;
		default:
			return -1;
	}
}

int typeclass(int type) {
	if (type >= int8 && type <= flt64) {
		return NUMTYPE;
	} else {
		if (type == boolean) {
			return BOOLTYPE;
		} else {
			if (type <= str) {
				return LITERAL;
			}
			return 0;	
		}
	}
}
