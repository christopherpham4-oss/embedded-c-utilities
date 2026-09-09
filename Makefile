#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# <Put a Description Here>
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#      <FILE>.i		- Preprocessed output of a single c source file
#	   <FILE>.asm   - Assembly output of a single c source file
#      c1m2.asm     - Disassembly of the final executable
#      <FILE>.o     - Object file of a single c source file 
#      compile-all  - Compile all source files to object files 
#      build        - Compile all source files and link into c1m2.out
#      clean        - Remove all generated build artifacts
#
# Platform Overrides:
#      PLATFORM=HOST    - Native compile with gcc
#      PLATFORM=MSP432  - Cross compile with arm-none-eabi-gcc
#
#------------------------------------------------------------------------------
include sources.mk

# Platform Overrides
PLATFORM = HOST

TARGET = c1final

ifeq ($(PLATFORM), MSP432)

# Architectures Specific Flags
LINKER_FILE = msp432p401r.lds
CPU = cortex-m4
ARCH = armv7e-m
SPECS = nosys.specs

# Compiler Flags and Defines
CC = arm-none-eabi-gcc
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
CFLAGS = -Wall -Werror -g -O0 -std=c99 \
         -mcpu=$(CPU) -mthumb -march=$(ARCH) \
         -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=$(SPECS)
CPPFLAGS = -DMSP432 -DCOURSE1 -DVERBOSE $(INCLUDES) -MD -MP
LDFLAGS = -Wl,-Map=$(TARGET).map -T $(LINKER_FILE)

else 

CC = gcc
OBJDUMP = objdump
SIZE = size
CFLAGS = -Wall -Werror -g -O0 -std=c99
CPPFLAGS = -DHOST -DCOURSE1 -DVERBOSE $(INCLUDES) -MD -MP
LDFLAGS = -Wl,-Map=$(TARGET).map

endif

OBJS = $(SOURCES:.c=.o)

%.i : %.c
	$(CC) -E $< $(CPPFLAGS) $(CFLAGS) -o $@
 
%.asm : %.c
	$(CC) -S $< $(CPPFLAGS) $(CFLAGS) -o $@
 
$(TARGET).asm : $(TARGET).out
	$(OBJDUMP) -d $< > $@
 
%.o : %.c
	$(CC) -c $< $(CPPFLAGS) $(CFLAGS) -o $@
 
.PHONY: compile-all
compile-all : $(OBJS)
 
.PHONY: build
build : $(TARGET).out
 
$(TARGET).out : $(OBJS)
	$(CC) $(OBJS) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
	$(SIZE) -Atd $@
 
.PHONY: clean
clean :
	rm -f $(SOURCES:.c=.o) $(SOURCES:.c=.d) $(SOURCES:.c=.i) $(SOURCES:.c=.asm) \
	      $(TARGET).out $(TARGET).map $(TARGET).asm