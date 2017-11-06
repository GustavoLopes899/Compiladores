project = mypas

INCLFLG = -I.
OPTFLAG = -g
CFLAGS  = $(OPTFLAG) $(INCLFLG)

$(project): $(project).o gettoken.o parser.o keywords.o symtab.o

clean:
	$(RM) *.o

mostlyclean: clean
	$(RM) *~
