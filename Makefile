# PS2 Toolchain
CC  = mips64r5900el-ps2-elf-gcc
CXX = mips64r5900el-ps2-elf-g++
AS  = mips64r5900el-ps2-elf-as

# Flags
CFLAGS  = -Wall -O2 -Isrc -Isrc/asm -Isrc/cpp
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = 

# Source files
C_SRCS   = $(wildcard src/*.c)
CPP_SRCS = $(wildcard src/cpp/*.cpp)
ASM_SRCS = $(wildcard src/asm/*.S)

# Object files
C_OBJS   = $(C_SRCS:.c=.o)
CPP_OBJS = $(CPP_SRCS:.cpp=.o)
ASM_OBJS = $(ASM_SRCS:.S=.o)

OBJS = $(C_OBJS) $(CPP_OBJS) $(ASM_OBJS)

# Output
TARGET = browser.elf

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CXX) $(OBJS) -o $(TARGET)

# Compile rules
src/%.o: src/%.c
    $(CC) $(CFLAGS) -c $< -o $@

src/cpp/%.o: src/cpp/%.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

src/asm/%.o: src/asm/%.S
    $(CC) -c $< -o $@

clean:
    rm -f $(OBJS) $(TARGET)

.PHONY: all clean
