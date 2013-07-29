###############################################################################
#	makefile
#    by Matthias Simons, based on the makefile
#	 by Alex Chadwick with suggestions from Coronax's Project Blog
#
#	A makefile script for generation of raspberry pi kernel images.
###############################################################################

# The toolchain to use. arm-none-eabi works, but there does exist 
# arm-bcm2708-linux-gnueabi.
ARMGNU ?= arm-none-eabi

# The intermediate directory for compiled object files.
BUILD = build/

# The directory in which source files are stored.
SOURCE = source/

# The name of the output file to generate.
TARGET = kernel.img

# The name of the assembler listing file to generate.
LIST = kernel.list

# The name of the map file to generate.
MAP = kernel.map

# The name of the linker script to use.
LINKER = kernel.ld

# The names of all object files that must be generated. Deduced from the 
# assembly code files in source.
C_OBJECTS := $(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c))
ASM_OBJECTS := $(patsubst $(SOURCE)%.s,$(BUILD)%.o,$(wildcard $(SOURCE)*.s))
OBJECTS = $(ASM_OBJECTS) $(C_OBJECTS)

# Rule to make everything.
all: $(TARGET) $(LIST)

# Rule to remake everything. Does not include clean.
rebuild: all

# Rule to make the listing file.
$(LIST) : $(BUILD)output.elf
	$(ARMGNU)-objdump -d $(BUILD)output.elf > $(LIST)

# Rule to make the image file.
$(TARGET) : $(BUILD)output.elf
	$(ARMGNU)-objcopy $(BUILD)output.elf -O binary $(TARGET) 

# Rule to make the elf file.
$(BUILD)output.elf : $(OBJECTS) $(LINKER)
	$(ARMGNU)-ld --no-undefined $(OBJECTS) -Map $(MAP) -o $(BUILD)output.elf -T $(LINKER) -LC:\yagarto-20121222\arm-none-eabi\lib -lc -lm -lg -lnosys

# Rule to make the object files.
$(BUILD)%.o: $(SOURCE)%.s
	$(ARMGNU)-as -I $(SOURCE) $< -o $@
$(BUILD)%.o: $(SOURCE)%.c 
	$(ARMGNU)-gcc -mcpu='arm1176jz-s' -I $(SOURCE) $< -c -o $@

# $(BUILD):
#	mkdir $@

# Rule to clean files.
clean : 
#	-rm -rf $(BUILD)
	-rm -f $(BUILD)output.elf
	-rm -f $(BUILD)*.o
	-rm -f $(TARGET)
	-rm -f $(LIST)
	-rm -f $(MAP)