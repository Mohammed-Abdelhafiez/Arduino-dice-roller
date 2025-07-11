/**
 * ARDUINO DUAL 7-SEGMENT DICE ROLLER WITH SOUND EFFECTS
 * =====================================================
 * 
 * Project Description:
 * A multiplayer electronic dice roller that simulates two 6-sided dice with:
 * - Realistic rolling animations
 * - Tactile feedback via passive buzzer
 * - Two-player control (either button triggers both dice)
 * 
 * Key Features:
 * 1. HARDWARE:
 *    - 2x 7-segment displays (74LS48 BCD decoders, 3-bit input)
 *    - 2x Pushbuttons with external pull-up resistors
 *    - 1x Passive buzzer (PWM-controlled sound effects)
 * 
 * 2. SOFTWARE:
 *    - Synchronized visual/sound effects
 *    - Random number generation with proper seeding
 *    - Debounced button inputs
 * 
 * 3. USER EXPERIENCE:
 *    - Either player can initiate rolls
 *    - "Tumbling" sound during animation
 *    - Satisfying "thud" when dice settle
 * 
 * Wiring Guide:
 *    Displays:
 *    - Die 1: Pins 3(A),4(B),5(C)
 *    - Die 2: Pins 8(A),9(B),10(C)
 *    - D pins grounded (1-6 range)
 *    Buttons:
 *    - Player 1: Pin 2 to GND (external pull-up)
 *    - Player 2: Pin 11 to GND (external pull-up)
 *    Buzzer:
 *    - Pin 6(+) to buzzer, GND(-) with 100Ω resistor
 * 
 * Created: 09/07/2025
 * Author: Mohamed Mahmoud Abdelhafiez
 */

// ========================
// HARDWARE CONFIGURATION
// ========================

// ======== BCD PIN CONFIGURATION ========
const int seg1_pins[3] = {3, 4, 5};    // Die 1: 74LS48 A, B, C (D grounded)
const int seg2_pins[3] = {8, 9, 10};   // Die 2: 74LS48 A, B, C (D grounded)

// ======== BUTTON PINS ========
const int button1 = 2;    // Trigger (active LOW)
const int button2 = 11;   // Trigger (active LOW)

// ======== BUZZER SETUP ========
const int buzzerPin = 6;  // PWM pin for buzzer

// ========================
// INITIALIZATION
// ========================
void setup() 
{
  // Initialize BCD decoder pins as outputs
  for( int i = 0; i < 3; i++)
  {
    pinMode(seg1_pins[i], OUTPUT);
    pinMode(seg2_pins[i], OUTPUT);
    digitalWrite(seg1_pins[i], LOW); // Ensure clean startup
    digitalWrite(seg2_pins[i], LOW);
  }
  
  // Initialize buttons (external pull-up = INPUT mode) 
  pinMode(button1, INPUT);  // No internal pull-up
  pinMode(button2, INPUT);  // No internal pull-up

  // Initialize buzzer
  pinMode(buzzerPin, OUTPUT);  
  noTone(buzzerPin);           // Ensure silent startup

  // Seed random number generator with analog noise
  randomSeed(analogRead(0));
}

// ========================
// MAIN LOOP
// ========================
void loop() 
{
  // Trigger roll if either button is pressed (LOW signal)
  // Active LOW: Button press pulls pin to GND
  if( (digitalRead(button1) == LOW) || (digitalRead(button2) == LOW))
  {
    rollDice(20, 50);     // Animate rolling (20 cycles, 50ms delay)
    playStopSound();      // Play when dice stop
    showResult();         // Display final numbers
    delay(300);           // Debounce delay
  }
}

// ======== FUNCTIONS ========

/**
 * Simulates dice rolling animation on both displays.
 * @param count      Number of random numbers generated (animation length)
 * @param delayTime  Delay between number changes (ms)
 */
void rollDice(int count, int delayTime)
{
  for(int i = 0; i < count; i++)
  {
    playRollSound(i * 0.5);   // Play during animation
    // Display numbers on both dice simultaneously
    showNumber(random(1, 7), seg1_pins);
    showNumber(random(1, 7), seg2_pins);
    delay(delayTime + i * 2); // Gradually slow down
  }
}

/**
 * Displays the final dice results (no animation).
 */
void showResult() {
  showNumber(random(1, 7), seg1_pins);
  showNumber(random(1, 7), seg2_pins);
}

/**
 * Outputs a number (1-6) to a 74LS48 BCD decoder (3-bit: A, B, C; D grounded).
 * @param number  Value to display (1-6)
 * @param pins    Array of 3 BCD pins (A, B, C)
 */
void showNumber(int number, const int pins[])
{
  // Send 3-bit BCD to 74LS48 (D is grounded)
  for(int i = 0; i < 3; i++)
  {
    digitalWrite(pins[i], number >> i & 0x01); // Extract bits 0,1,2
  }
}

/**
 * Plays a dice-rolling sound effect
 * @param duration  Sound length in milliseconds
 */
void playRollSound(int duration)
{
  for (int i = 0; i < duration; i++)
  {
    tone(buzzerPin, 500 + random(500), 20); // Random pitch (500-1000Hz)
    delay(20);
  }
  noTone(buzzerPin);  // Stop sound
}

/**
 * Plays a "settling" sound when dice stop
 */
void playStopSound()
{
  tone(buzzerPin, 200, 100); // Low pitch "thud"
  delay(100);
  noTone(buzzerPin);
}
 
