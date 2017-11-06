/**<parser.h>::**/
extern FILE *src;
extern int lookahead;

/*internal tokens*/

enum {
	int8 = 1,
	int16,
	int32,
	flt32,
	flt64,
	boolean,
	chr,
	str,
};

enum {
	NUMTYPE = 1,
	BOOLTYPE,		// ou LOGTYPE
	LITERAL,
};

/** syntax definitions **/

void declaratives (void);
void imperatives(void);
void mypas (void);
int varlist(void);
int vartype(void);
void stmtlist(void);
int isFIRST_E (void);
int typeclass(int);
void stmt(void);
int isotilde(void);

void E_(void);
int E(int);

void Start(void);

void R(void);

void T(void);

void Q(void);

void F(void);

// declarar funções que faltam de parser.c void mypas

