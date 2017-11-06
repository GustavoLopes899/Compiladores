/**<gettoken.c>::**/

#include <stdio.h>
#include <ctype.h>
#include <gettoken.h>
#include <string.h>
#include <keywords.h>

int linecount = 1;
int columncount = 0;
char lexeme[MAXSTRLEN+1];

void skipspaces(FILE *tape) {
	while (isspace(lexeme[0] = getc(tape)));
	if (lexeme[0] == '\n') {
		linecount++;
		columncount = 0;
	}
	ungetc(lexeme[0], tape);
}

int isID(FILE *tape) {
	int i = 0;
	if (isalpha(lexeme[i] = getc(tape))) {
		i++;
		while (isalnum(lexeme[i] = getc(tape)))
		if (i < MAXSTRLEN) {
			i++;
		}
		ungetc (lexeme[i], tape);
		columncount = i + columncount; 		//rever o columncount
		lexeme[i] = 0;
		if (i = iskeyword(lexeme)) {
			return i;
		}
		return ID;
	}
	ungetc (lexeme[i], tape);
	return 0;
}

int isDEC(FILE *tape) {
	int i = 0;
	if (isdigit(lexeme[i] = getc(tape))) {
		if (lexeme[i] == '0') {
			return DEC;
		}
		i++;
		while (isdigit(lexeme[i] = getc(tape))) {
			i++;
		}
		ungetc (lexeme[i], tape);
		return DEC;
    }
    ungetc (lexeme[i], tape);
    return 0;
}

int isASGNM(FILE *tape) {
	if ((lexeme[0] = getc(tape)) == ':') {
		if ((lexeme[1] = getc(tape)) == '=') {
			return ASGNM;
		}
		ungetc (lexeme[1], tape);
	}
	ungetc (lexeme[0], tape);
	return lexeme[0] = 0;
}

int isGEQ(FILE *tape) {
	if ((lexeme[0] = getc(tape)) == '>') {
		if ((lexeme[1] = getc(tape)) == '=') {
			return GEQ;
		}
		ungetc (lexeme[1], tape);
		ungetc (lexeme[0], tape);
		return 0;
	}
	ungetc (lexeme[0], tape);
	return 0;
}

int isNEQ(FILE *tape) {
	if ((lexeme[0] = getc(tape)) == '<') {
		if ((lexeme[1] = getc(tape)) == '>') {
			return NEQ;
		}
		ungetc (lexeme[1], tape);
		ungetc (lexeme[0], tape);
		return 0;
	}
	ungetc (lexeme[0], tape);
	return 0;
}

int isLEQ(FILE *tape) {
	if ((lexeme[0] = getc(tape)) == '<') {
		if ((lexeme[1] = getc(tape)) == '=') {
			return LEQ;
		}
		ungetc (lexeme[1], tape);
		ungetc (lexeme[0], tape);
		return 0;
	}
	ungetc (lexeme[0], tape);
	return 0;
}

int isNUM(FILE *tape) {
	int i = 0;
	int token = isDEC(tape);
	if ((lexeme[i] = getc(tape)) == '.') {
		if (token == 0) {
			i++;
			if (!isdigit(lexeme[i] = getc(tape))) {
				ungetc (lexeme[i],tape);
				ungetc (lexeme[--i],tape);
			return 0;
			}
		}
		token = FLT;
		while (isdigit(lexeme[i] = getc(tape))) {
			i++;
		}
		ungetc(lexeme[i], tape);
	} else {
		ungetc(lexeme[i], tape);
	}
	return token;
}

int gettoken(FILE *tape) {
	int token;
	skipspaces(tape);
	if ((token = isID(tape))    ||
		(token = isNUM(tape)) 	||
		(token = isNEQ(tape))   ||
		(token = isGEQ(tape)) 	||
		(token = isLEQ(tape)) 	||
		(token = isASGNM(tape)) ||
		(token = getc(tape))
	)
    return token;
}