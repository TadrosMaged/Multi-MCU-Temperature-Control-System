# Multi-MCU Temperature Management System with Error Handling

## Overview

This project implements a temperature management system using two microcontrollers (MCUs) to control a fan and a machine based on temperature readings. The system includes multiple states and error handling mechanisms, including normal, emergency, and abnormal states. The project demonstrates how MCU coordination can be used for complex temperature-based control and fault diagnosis.

## Components

### MCU1
- **Push Button**: Triggers state change based on temperature.
- **Temperature Sensor**: Measures the ambient temperature.
- **DC Motor (Fan)**: Controlled to adjust the speed based on temperature.
- **EEPROM**: Stores state information.

### MCU2
- **Servo Motor**: Adjusts position based on state.
- **3 LEDs**: Indicate different states (Green, Yellow, Red).
- **Potentiometer**: Controls the speed of the machine (DC motor).
- **DC Motor (Machine)**: Operates the machine.
- **Buzzer**: Alerts in case of error states.

## System Description

### MCU1 Responsibilities
1. Read the state from EEPROM to determine if it is in an abnormal state.
2. Measure the temperature.
3. Store the initial state as normal in EEPROM.
4. Control the fan speed based on temperature and send the temperature to MCU2 via UART.
5. If the push button is pressed and the temperature is between 40°C and 50°C, send a shutdown code to MCU2 via UART.

### MCU2 Responsibilities
1. Receive messages from MCU1 via UART and act accordingly.
2. Control the speed of the machine (DC motor) using the potentiometer.
3. Manage the LEDs and buzzer to indicate different states.
4. Adjust the servo motor position based on state.
5. Implement emergency and abnormal state handling.

## States

### Normal State
- **Below 20°C**: Stop the fan and light the green LED.
- **20°C - 40°C**: Increase fan speed proportionally to the temperature; light the yellow LED.
- **40°C - 50°C**: Run the fan at maximum speed; light the red LED and stop the machine if the push button is pressed.
- **Above 50°C**: Enter emergency state.

### Emergency State
- Begin timing.
- Run the fan at maximum speed.
- Light the red LED and activate the buzzer.
- If the emergency state persists for 7 seconds, transition to abnormal state:
  - Write abnormal state to EEPROM.
  - Activate the watchdog timer on MCU1.

### Abnormal State
- Run the fan at maximum speed.
- Light the red LED.
- Open the servo to 90 degrees.
- Stop the machine and activate the buzzer.

## Testing and Demonstration

1. **Temperature Sensor and Fan Function**: Use an oscilloscope to show the fan's response to temperature changes.
2. **Potentiometer and Machine Function**: Use an oscilloscope to demonstrate the potentiometer's effect on machine speed.
3. **Emergency State Function**: Show how the system reacts when entering the emergency state.
4. **Push Button Function**: Demonstrate how the push button affects system operation.
5. **Normal States**: Show system behavior across normal operating conditions.
6. **Temperature Recovery**: Display the transition back to normal states when the temperature decreases below 50°C.

## Setup

1. Connect all components as described in the system overview.
2. Flash the appropriate firmware onto MCU1 and MCU2.
3. Test each state and transition thoroughly.

## Contributing

Feel free to contribute by submitting issues, suggesting improvements, or making pull requests.

## License

This project is licensed under the [MIT License](LICENSE).

## Contact

For questions or further information, please contact Tadros Maged at tadrosmaged30@gmail.com
