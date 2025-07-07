# Makefile
# Properties
DESTINATION = firmware
DEVICE      = atmega328p
PARTNUMBER  = m328p
PROGRAMMER  = usbasp
INCLUDES    = $(addprefix -I, ./src/)
DEFINES	    = $(addprefix -D, F_CPU=8000000UL BAUD_RATE=9600UL U2X)

# Utilities
AVRDUDE     = avrdude -c $(PROGRAMMER) -p $(PARTNUMBER)
AVRGCC      = avr-gcc -mmcu=$(DEVICE) -Os -Wall $(DEFINES) $(INCLUDES)
AVROBJCOPY  = avr-objcopy --input-target elf32-avr --output-target ihex --verbose
AVROBJDUMP  = avr-objdump --disassemble
AVRSIZE     = avr-size --format=AVR --mcu=$(DEVICE)

# Source files
SOURCES = 									\
											\
	src/drivers/gpio.c						\
	src/drivers/timer_0.c					\
	src/drivers/uart.c						\
	src/drivers/ir_sensors.c				\
											\
    src/main.c 								\

# Object files
OBJECTS = $(patsubst src/%.c, target/%.o, $(SOURCES))

build: clean $(OBJECTS)
	@mkdir -p ./target  # Create the target directory if it doesn't exist
	@echo "Linking..."
	@$(AVRGCC) -o ./target/$(DESTINATION).elf $(OBJECTS)
	@$(AVROBJCOPY) ./target/$(DESTINATION).elf ./target/$(DESTINATION).hex
	@echo "INFO: build finished"

./target/%.o: ./src/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(AVRGCC) -c $< -o $@

clean:
	@rm --force --recursive --verbose ./target
	@echo "INFO: clean finished"

check:
	@$(AVRDUDE)
	
erease:
	@$(AVRDUDE) -e

upload:
	@$(AVRDUDE) -U flash:w:./target/$(DESTINATION).hex:i

disasm: ./target/$(DESTINATION).elf
	@$(AVROBJDUMP) ./target/$(DESTINATION).elf

size:	./target/$(DESTINATION).elf
	@$(AVRSIZE) ./target/$(DESTINATION).elf 

fuses-default:
	@$(AVRDUDE) -U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

fuses-no-divider-ext-clk:
	@$(AVRDUDE) -U lfuse:w:0xff:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

eeprom-write-firmware-version:
	@$(AVRDUDE) -U eeprom:w:version:r

firmware-version:
	@$(AVRDUDE) -U eeprom:r:-:r | hexdump -C
