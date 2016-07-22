CC=gcc
CFLAGS=-Wall
OFLAGS=-c
COVER=-Wall -ftest-coverage -fprofile-arcs
DEBUG=-Wall -g -D DEBUG
FILES=StringToNPAlpha.o
#HEADERS=TODO
EXE=StringToNPAlpha
CLEANFILES=$(EXE) a.out *.o *.gcov *.gcno *.gcda

TODO : $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(FILES) -o $(EXE)
%.o : %.c 
	$(CC) $(OFLAGS) $<
.PHONY : coverage
coverage :
	$(CC) $(COVER) $(FILES:.o=.c) -o $(EXE)
.PHONY : debug
debug :
	$(CC) $(DEBUG) $(FILES:.o=.c) -o $(EXE)
.PHONY : clean
clean :
	rm -f $(CLEANFILES)
