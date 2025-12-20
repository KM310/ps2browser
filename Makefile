# ================================
#  PS2 Linux Browser – Makefile
#  Zielplattform: native PS2 Linux (MIPS)
# ================================

# Native Compiler auf PS2 Linux
CC      = gcc

# Compiler-Flags
CFLAGS  = -O2 -Wall

# C-Quellcode
SRC_C = \
    src/main.c \
    src/http.c \
    src/html_parser.c \
    src/render.c \
    src/js_vm.c

# ASM-Quellcode (Großes .S = durch Preprocessor laufend)
SRC_ASM = \
    src/asm/string_opt.S \
    src/asm/mem_opt.S

# Objektdateien
OBJ = $(SRC_C:.c=.o) $(SRC_ASM:.S=.o)

# Zielname
TARGET = ps2browser

.PHONY: all clean

# Standardziel
all: $(TARGET)

# Linken
$(TARGET): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $(OBJ)

# C-Dateien kompilieren
src/%.o: src/%.c
    $(CC) $(CFLAGS) -c $< -o $@

# ASM-Dateien kompilieren
src/asm/%.o: src/asm/%.S
    $(CC) $(CFLAGS) -c $< -o $@

# Aufräumen
clean:
    rm -f $(OBJ) $(TARGET)
