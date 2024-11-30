# Reaction Time Measurement System  

## Overview
This project implements a reaction time measurement system using an AVR microcontroller (mega328p). The system measures the time taken for a user to react to a stimulus and displays the results on an LCD screen.  
In fact this is an assigment for laboratory work #1 from Cornell University ECE 4760 course - Spring 2012.  

## Features
- **High Precision:** Measures reaction time with 16µs resolution.
- **User-Friendly Display:** Outputs results on an LCD screen.
- **Score Persistence:** Saves high scores in EEPROM memory.
- **PC Connectivity:** UART communication for monitoring and debugging.

## How to Use
1. **Hardware Setup:**
   - Connect the AVR microcontroller to the required peripherals (buttons, LCD, buzzer, etc.).
   - Assemble the PCB as outlined in the KiCad design files.

2. **Firmware Deployment:**
   - Use the provided `Makefile` to build the project using the AVR GCC toolchain.
   - Upload the firmware to the microcontroller using AVRDUDE.

3. **Operation:**
   - Power the device and follow the on-screen prompts.
   - Monitor reaction times on the LCD and see the system information using the UART interface.

4. **Simulation:**
   - Run the simulation using Proteus for testing and debugging without hardware.

## Dependencies
- AVR GCC Toolchain
- AVRDUDE for uploading firmware
- Terminal program for UART communication

## License
This project is licensed under the [MIT License](LICENSE).