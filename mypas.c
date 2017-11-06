/**<parser-main.c>::**/
#include <stdio.h>
#include <stdlib.h>
#include <gettoken.h>
#include <parser.h>

FILE *src;

int main(int argc, char const *argv[]) {
	if (argc == 1) {
		src = stdin;
	} else {
		src = fopen(argv[1], "r");
		if (src == NULL) {
			fprintf(stderr, "%s: cannot open %s... exiting with err status %d\n", argv[0], argv[1], -2);
			exit (-2);
		}
	}

	lookahead = gettoken(src);

	mypas();

	return 0;
}