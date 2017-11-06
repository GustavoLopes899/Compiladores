/**<gettoken.h>::**/

//#include <stdio.h>

#define MAXSTRLEN 1024

/** internal tokens **/

enum {
	ID = 0x10000,			// 65536
	DEC,
	FLT,
	EQL,
	LEQ,
	GEQ,
	NEQ,
	ASGNM,
};

// Arrumar, talvez mudar para o gettoken.c
/*char *token_info[] = {
	"ID",
	"DEC",
	"FLT",
	"<>",
	">=",
	"<=",
	":=",
	"(",
	")",
	"",
};*/

extern int linecount;
extern int columncount;

extern char lexeme[MAXSTRLEN + 1];

/** parser-lexer interface **/

int gettoken(FILE *);
