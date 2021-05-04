# Based on https://stackoverflow.com/a/30602701

INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXTERNAL_INC_DIR := ../
# INC_DIR += $(EXTERNAL_INC_DIR)

EXE := $(BIN_DIR)/mct

# SRC := $(wildcard $(SRC_DIR)/*.c)
SRC := $(SRC_DIR)/mcu_main.c \
	$(SRC_DIR)/mcu_suite1.c

# OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))


CC=gcc
CPPFLAGS := -Iinclude -MMD -MP # -I is a preprocessor flag, not a compiler flag
CFLAGS=-W -Wall -pedantic
LDFLAGS  :=               # -L is a linker flag, -> path to the libraries to be linked to (see it as include_dir : -Lpath/to/ldlibs)
LDLIBS   :=                 # Left empty if no libs are needed -> The libraries to link to




.PHONY: all clean mr_proper

all: $(EXE)


# Linkage of the objects files into one executable. Create BIN_DIR if it doesn't exist
# $^ -> contains the list of all dependencies of the rule
$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compilation of the source files into objects files. Create OBJ_DIR if it doesn't exist
# %@ -> contains the target of the rule (here %.o expanded)
# %< -> contains the first dependency of the rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@


tests: all
	./$(EXE)

# clean:
# 	rm -f $(ODIR)/*.o
clean:
	$(RM) -r $(OBJ_DIR)

mr_proper: clean
	$(RM) -r $(BIN_DIR)

-include $(OBJ:.o=.d)

# 	macro that must end with semicolon shall be lowercasae.
# 	macro that dont need semicolon shall be uppercase.
# 	internal macro shall be ??? upper or lower ?? with __MACRO__ ???
