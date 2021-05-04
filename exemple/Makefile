CC=gcc


# BIN		:= bin
# INCLUDE := src/test_suites
# SOURCEDIR := src

INCLUDE :=.
CFLAGS=-W -Wall -pedantic -I$(INCLUDE)


SRC := mcu_main.c \
	mcu_suite1.c

ODIR := obj
_OBJ = $(SRC:.c=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


all: mct 

# $^ -> contains the list of all dependencies of the rule
# Linkage of the objects files into one executable
mct: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


# %@ -> contains the target of the rule (here %.o expanded)
# %< -> contains the first dependency of the rule
# Compilation of the source files into objects files
$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c  $<


tests: mct
	./mct

.PHONY: clean mr_proper
	
clean:
	rm -f $(ODIR)/*.o

mr_proper: clean
	rm mct

# 	macro that must end with semicolon shall be lowercasae.
# 	macro that dont need semicolon shall be uppercase.
# 	internal macro shall be ??? upper or lower ?? with __MACRO__ ???
