# Simple makefile that compiles the StringTONPAlpha program

CC=gcc # Change for compiler of choice
CFLAGS=-Wall # Flags for compiling the source files
OFLAGS=-c # Flags for compiling object files
# Flags for testing coverage of the program
COVER=-Wall -ftest-coverage -fprofile-arcs
DEBUG=-Wall -g -D DEBUG # Flags for debugging the program
FILES=StringToNPAlpha.o # Input object file names for compiling the program
EXE=StringToNPAlpha # Output executable name of the program
# used for cleaning out files created by the make file
CLEANFILES=$(EXE) a.out *.o *.gcov *.gcno *.gcda

StringToAlpha : $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o $(EXE)
%.o : %.c 
	$(CC) $(CFLAGS) $(OFLAGS) $<
.PHONY : coverage
coverage :
	$(CC) $(COVER) $(FILES:.o=.c) -o $(EXE)
.PHONY : debug
debug :
	$(CC) $(DEBUG) $(FILES:.o=.c) -o $(EXE)
.PHONY : clean
clean :
	rm -f $(CLEANFILES)
