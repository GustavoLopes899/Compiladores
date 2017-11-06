/**<keywords.c>::**/

#include <keywords.h>
#include <string.h>

char *keyword[] = {
	"begin",
	"var",
	"byte",
	"word",
	"integer",
	"real",
	"double",
	"boolean",
	"char",
	"string",
	"text",
	"if",
	"then",
	"else",
	"while",
	"do",
	"repeat",
	"until",
	"not",
	"end"
};

int iskeyword(char const * identifier) {
	int i;
	for (i = BEGIN; i <= END; i++)
		if (strcmp(keyword[i - BEGIN], identifier) == 0) {
			return i;
		}			
	return 0;
}

char* printkeyword(int lookahead) {
	return keyword[lookahead - BEGIN];
}
