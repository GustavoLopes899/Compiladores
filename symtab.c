/**@<symtab.c>::**/

#include <stdio.h>
#include <gettoken.h>
#include <symtab.h>
#include <string.h>

SYMTAB symtab[MAXSTBENTRIES+1];

int symtab_nextentry = 1;

int symtab_lookup(char const *query) {
	int i;
	
	for (i = 1; i < symtab_nextentry; i++) {
		if (strcmp(symtab[i].name, query) == 0) return i;
	}
	return 0;
}

int symtab_append(char const *newname) {
	int i = symtab_lookup(newname);

	if (i == 0) {
		strcpy(symtab[symtab_nextentry].name, newname);
		return symtab_nextentry++;
	}

	return 0/* means duplicate symbol declaration*/;
}

void symtab_settype(int vtype, int a) {
	int i;
	for(i = a; i < symtab_nextentry; i++) {
		symtab[i].vtype = vtype;
	}
}