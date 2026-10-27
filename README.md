# STC89C52RC Digital Clock

A digital clock project based on the **STC89C52RC (8051-compatible microcontroller)**, developed using C and Keil C51. The project integrates LCD display, Timer0 interrupts, button-based time and date adjustment, and UART serial transmission.

The clock was developed and tested on a physical development board.

## Features

- **Real-Time Clock Display**: Displays time in 12-hour format with AM/PM indication.
- **Date Display**: Displays year, month, and day on an LCD1602.
- **Timer0 Interrupt**: Uses Timer0 interrupts for periodic timekeeping.
- **Button-Based Adjustment**: Supports manual adjustment of hours, minutes, seconds, AM/PM, year, month, and day.
- **Calendar Rollover**: Automatically updates the date when the clock crosses midnight, including month and year transitions.
- **Leap Year Handling**: Implements leap-year rules for February during automatic date rollover and manual day adjustment.
- **UART Serial Transmission**: Sends the current time (`HH:MM:SS`) to a serial terminal when the transmission button is pressed.
- **Modular Code Structure**: Separates LCD, timer, delay, and UART functions into individual modules.

## Hardware and Development Environment

- **Microcontroller**: STC89C52RC
- **Architecture**: 8051-compatible 8-bit MCU
- **Crystal Frequency**: 11.0592 MHz
- **Timer Configuration**: Timer0, Mode 1, 16-bit timer, 12T mode
- **Display**: LCD1602
- **Development IDE**: Keil µVision / Keil C51
- **Programming Language**: C
- **Serial Communication**: UART, 4800 bps

## Technical Implementation

### 1. Timer0 Interrupt-Based Timekeeping

Timer0 is configured in 16-bit Mode 1. With an 11.0592 MHz crystal and 12T operation, the timer is reloaded with an initial value of 64614 to generate an approximately 1 ms interval.

The interrupt service routine counts timer interrupts and updates the clock every 1000 ticks.

### 2. Button Input and State Machine

A switch-case state machine manages the clock-setting process. Buttons are used to increment values, decrement values, and move between configuration states.

A software debounce delay is applied to button inputs to reduce false triggers caused by mechanical contact bounce.

### 3. Calendar Rollover and Leap Year Calculation

The calendar logic handles different month lengths and Gregorian leap-year rules. When the clock reaches midnight, the date is incremented and the month or year is updated when necessary.

The current implementation supports manual day adjustment based on the selected month and year. Automatic validation of the existing day value after changing the year or month is not yet implemented.

### 4. UART Serial Transmission

The UART is configured for 4800 bps. When the transmission button is pressed, the microcontroller sends the current time in the following format:

`HH:MM:SS`

The message ends with carriage return and line feed (`\r\n`) for convenient display in a serial terminal.

## Project Structure

```text
STC89C52RC-Digital-Clock/
├── main.c
├── LCD1602.c
├── LCD1602.h
├── Delay.c
├── Delay.h
├── Timer0.c
├── Timer0.h
├── UART.c
└── UART.h
```

## Build and Run

1. Open the project in Keil µVision with the Keil C51 toolchain.
2. Add all required `.c` source files to the project and configure the target for the STC89C52RC.
3. Build the project and check the compilation results.
4. Download the generated firmware to the microcontroller using a compatible programmer.
5. Connect the LCD1602, buttons, and UART interface according to the hardware configuration.
6. Use the buttons to adjust the time and date.
7. Press the UART transmission button and observe the output with a serial terminal configured for 4800 bps.

## Learning Outcomes

Through this project, I gained hands-on experience with:

- 8051-compatible MCU programming using C
- Timer configuration and interrupt service routines
- GPIO input handling and software debouncing
- LCD1602 interfacing
- State-machine-based application logic
- Calendar rollover and leap-year calculation
- UART initialization and serial data transmission
- Modular firmware development and hardware testing

## Future Improvements

- Validate the day value automatically when the year or month changes.
- Improve shared-variable handling between the main loop and interrupt service routines.
- Expand serial communication functionality and error handling.
- Explore additional MCU platforms and peripheral interfaces.

