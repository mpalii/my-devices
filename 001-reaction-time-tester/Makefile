# Makefile
# Properties
DESTINATION = firmware
DEVICE      = atmega328p
PROGRAMMER  = usbasp-clone
SCORE_ADDRESS = 0x0000

# Utilities
AVRDUDE     = avrdude -c $(PROGRAMMER) -p $(DEVICE)
AVRGCC      = avr-gcc -mmcu=$(DEVICE) -Os -Wall -DF_CPU=18432000UL -DSCORE_ADDRESS=$(SCORE_ADDRESS)
AVROBJCOPY  = avr-objcopy --input-target elf32-avr --output-target ihex --verbose
AVROBJDUMP  = avr-objdump --disassemble
AVRSIZE     = avr-size --format=AVR --mcu=$(DEVICE)

# Source files
SOURCES = \
    src/main.c \
    src/app/launcher.c \
    src/app/metrics.c \
    src/drivers/button.c \
    src/drivers/buzzer.c \
    src/drivers/gpio.c \
    src/drivers/lcd1602.c \
    src/drivers/led.c \
    src/drivers/score_reset.c \
    src/drivers/uart.c \
    src/finite_automaton/state_false_start.c \
    src/finite_automaton/state_machine.c \
    src/finite_automaton/state_measuring.c \
    src/finite_automaton/state_ready.c \
    src/finite_automaton/state_result.c \
    src/finite_automaton/state_timeout.c \
    src/finite_automaton/state_wait.c \
    src/task_manager/button_handling_task.c \
    src/task_manager/eeprom_score_saving_task.c \
    src/task_manager/lcd1602_rendering_task.c \
    src/task_manager/scheduler.c \
    src/task_manager/serial_transmission_task.c \
    src/task_manager/state_machine_handling_task.c

# Object files
OBJECTS = $(patsubst ./src/%.c, ./target/%.o, $(SOURCES))

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
	@rm -rf ./target
	@echo "INFO: clean finished"

disasm: ./target/$(DESTINATION).elf
	@$(AVROBJDUMP) ./target/$(DESTINATION).elf

size: ./target/$(DESTINATION).elf
	@$(AVRSIZE) ./target/$(DESTINATION).elf

check:
	@$(AVRDUDE)

erease:
	@$(AVRDUDE) -e

upload:
	@$(AVRDUDE) -U flash:w:./target/$(DESTINATION).hex:i

fuses-default:
	@$(AVRDUDE) -U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

fuses-no-divider-ext-clk:
	@$(AVRDUDE) -U lfuse:w:0xff:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m
