# ================================
#  PS2 Linux Browser – Makefile
#  Zielplattform: native PS2 Linux (MIPS)
# ================================

# Native Compiler auf PS2 Linux
CC      = gcc
CXX     = g++

# Compiler-Flags
CFLAGS   = -O2 -Wall -Isrc -Isrc/asm -Isrc/cpp
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti

# C-Quellcode
SRC_C = \
    src/main.c \
    src/http.c \
    src/html_parser.c \
    src/render.c \
    src/js_vm.c

# C++-Quellcode
SRC_CPP = \
    src/cpp/buffer.cpp \
    src/cpp/buffer_c_api.cpp

# ASM-Quellcode (Großes .S = durch Preprocessor laufend)
SRC_ASM = \
    src/asm/string_opt.S \
    src/asm/mem_opt.S

# Objektdateien
OBJ = \
    $(SRC_C:.c=.o) \
    $(SRC_CPP:.cpp=.o) \
    $(SRC_ASM:.S=.o)

# Zielname (KEIN .elf!)
TARGET = ps2browser

.PHONY: all clean

# Standardziel
all: $(TARGET)

# Linken (C++ Linker, damit C++ + ASM + C funktioniert)
$(TARGET): $(OBJ)
    $(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# C-Dateien kompilieren
src/%.o: src/%.c
    $(CC) $(CFLAGS) -c $< -o $@

# C++-Dateien kompilieren
src/cpp/%.o: src/cpp/%.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# ASM-Dateien kompilieren
src/asm/%.o: src/asm/%.S
    $(CC) $(CFLAGS) -c $< -o $@

# Aufräumen
clean:
    rm -f $(OBJ) $(TARGET)
