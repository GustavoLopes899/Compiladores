/**@<symtab.h>::**/

#define MAXSTBENTRIES	0X1000

typedef struct {
	char name[MAXSTRLEN+1];
	int  vtype;
} SYMTAB;

extern SYMTAB symtab[];

extern int symtab_nextentry;

int symtab_lookup(char const *query);

int symtab_append(char const *newname);

void symtab_settype(int, int);