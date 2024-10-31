# Microcontroller Stopwatch and Clock Project

## Description

This project implements a stopwatch and clock functionality on a microcontroller using C programming. It utilizes an STM32 microcontroller and a 16x2 character LCD display to provide timekeeping features and stopwatch functionality.

## System Requirements

- **Microcontroller:** STM32
- **LCD Display:** 16x2 character LCD
- **Buttons:** Mode, Edit, Up, Down, Left, Right, OK
- **USART Communication:** USART1 interface
- **Clock Source:** External crystal oscillator (16MHz)
- **Programming Language:** C
- **Development Environment:** STM32CubeIDE

## Installation

1. Clone the repository to your local machine.
2. Set up the STM32CubeIDE development environment.
3. Connect the microcontroller, LCD display, and buttons as per the hardware requirements.
4. Compile and upload the code to the microcontroller.

## Usage

1. Power on the microcontroller.
2. Use the buttons to switch between clock and stopwatch modes, enter edit mode, adjust settings, and confirm changes.
3. Verify the USART communication by sending and receiving data from external devices.

## Features

- **Clock Mode:** Display current time and date.
- **Stopwatch Mode:** Start, stop, and reset functionality.
- **Edit Mode:** Modify time and date settings.
- **USART Communication:** Communicate with external devices.

## Test Cases

1. **Clock Mode Display Test:** Verify accuracy of time and date displayed.
2. **Stopwatch Functionality Test:** Ensure correct operation of the stopwatch.
3. **Edit Mode Test:** Verify users can modify settings without errors.
4. **USART Communication Test:** Test reliability of communication with external devices.
5. **Button Input Test:** Verify recognition and response of button inputs.
6. **System Reliability Test:** Evaluate stability and reliability during continuous operation.

## Contributing

Contributions are welcome. Please fork the repository and submit pull requests with any improvements or fixes.

## License

This project is licensed under the MIT License.

## Authors

- [Author Name](link-to-author-profile)



## Test Cases:

### Clock Mode Display Test:

**Objective:** Verify the accuracy of time and date displayed in Clock Mode.  
**Inputs:** None.  
**Expected Output:** Display shows the current time and date accurately.

### Stopwatch Functionality Test:

**Objective:** Ensure the stopwatch operates correctly.  
**Inputs:**
- Start button press.
- Stop button press.
- Reset button press.  
**Expected Output:** Stopwatch starts, pauses, and resets accurately in response to button presses.

### Edit Mode Test:

**Objective:** Verify users can enter Edit Mode and modify time and date settings.  
**Inputs:**
- Enter Edit Mode button press.
- Up/Down button presses to adjust settings.
- OK button press to confirm changes.  
**Expected Output:** Edit Mode entered successfully. Users can navigate through settings, adjust values, and confirm changes without errors.

### USART Communication Test:

**Objective:** Ensure reliable communication between microcontroller and external devices over USART.  
**Inputs:** Send and receive data via USART.  
**Expected Output:** Data sent from microcontroller is received accurately by external device. Data sent from external device is received accurately by microcontroller.

### Button Input Test:

**Objective:** Test recognition and response of button inputs.  
**Inputs:** Press various buttons (Mode, Edit, Up, Down, Left, Right, OK).  
**Expected Output:** Corresponding actions performed based on button presses without errors.

### System Reliability Test:

**Objective:** Evaluate system stability and reliability during continuous operation.  
**Inputs:** Continuous operation without interruption.  
**Expected Output:** System operates reliably without crashes, freezes, or unexpected behavior over extended duration.

## Acknowledgements

Special thanks to [Contributor Name](link-to-contributor-profile) for their assistance.

Feel free to customize the README to fit your project's specific details and requirements!

