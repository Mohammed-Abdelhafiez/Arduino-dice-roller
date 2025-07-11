# Arduino Dual Dice Roller with LED Animation and Sound

🎲 A multiplayer dice roller built with Arduino, using 7-segment displays and a passive buzzer for synchronized sound and visual effects.

## 🚀 Features
- Dual 6-sided dice simulation
- LED animation while rolling
- Tactile feedback using PWM buzzer
- Two pushbuttons for multiplayer control
- Debounced input & random number logic

## 🧰 Hardware Used
- Arduino Uno (or compatible)
- 2x 7-segment displays (via 74LS48 BCD decoders)
- 2x pushbuttons with external pull-ups
- 1x passive buzzer (PWM)
- Resistors, breadboard, jumper wires
## 🔌 Wiring Summary

**Displays:**
- Die 1: Pins 3(A), 4(B), 5(C)  
- Die 2: Pins 8(A), 9(B), 10(C)  
- D pins grounded

**Buttons:**
- Player 1: Pin 2  
- Player 2: Pin 11  
(Connected to GND with external pull-ups)

**Buzzer:**
- Pin 6 to buzzer (+)
- GND through 100Ω resistor

## 🎮 Usage

1. Power on the Arduino
2. Press any button to roll both dice
3. Enjoy the tumbling LED animation and buzzer "thud"

## 📂 Files

- "dice_roller.ino" - Arduino sketch
- "portfolio.pdf" - Project documentation
