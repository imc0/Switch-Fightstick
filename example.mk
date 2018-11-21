# Makefile for the example Joystick app

# Name of the app we are building
TARGET   = example
# list of the C source files to build
SOURCES  = $(TARGET).c

# where to find the Joystick include file
INCLUDES = -I.
# how to link the Joystick library
LIBS     = -L. -lJoystick
# architecture we are building for
MCU      = at90usb1286
# flags for optimisation
OPTFLAGS = -Os -gdwarf-2 -g2
# any other flags desired
CFLAGS   = -Wall
# The following ABI flags might change the internal representations of
# structures and should match the flags used when the library was compiled.
ABIFLAGS = -fshort-enums -fpack-struct -funsigned-char -funsigned-bitfields

# Programs we are using to compile
CC       = avr-gcc
OBJCOPY  = avr-objcopy
SIZE     = avr-size

# Directory in which we place the .o files
OBJDIR   = obj

# This calculates the names and locations of the .o files, given the sources
OBJECTS := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

# These are the default targets to make
all: prep hex size

# The shortcuts 'elf' and 'hex' really mean TARGET.elf and TARGET.hex
hex: $(TARGET).hex
elf: $(TARGET).elf

# The prep function just creates the object directory if it doesn't exist
prep:
	@test -d $(OBJDIR) || mkdir -p $(OBJDIR)

# How to compile C files
$(OBJDIR)/%.o: %.c
	$(CC) -c $(OPTFLAGS) -mmcu=$(MCU) $(ABIFLAGS) $(INCLUDES) $(CFLAGS) $< -o $@

# How to link objects into an ELF file
$(TARGET).elf: $(OBJECTS)
	$(CC) -mmcu=$(MCU) $(OBJECTS) $(LIBS) $(OPTFLAGS) -o $@

# How to turn the ELF file into hex
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -g $< $@

# Prints out some information about the size of the application
size: $(TARGET).elf
	$(SIZE) --mcu=$(MCU) --format=avr $<

# Remove compiled objects created by this Makefile
clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).hex
