/**<keywords.h>::**/

/* internal tokens */

enum {
	BEGIN = 2048,
	VAR,
	BYTE,
	WORD,
	INTEGER,
	REAL,
	DOUBLE,
	BOOLEAN,
	CHAR,
	STRING,
	TEXT,
	IF,
	THEN,
	ELSE,
	WHILE,
	DO,
	REPEAT,
	UNTIL,
	NOT,
	END
};

int iskeyword(char const *);

char* printkeyword(int);
