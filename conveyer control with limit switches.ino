#include <AccelStepper.h>

// Define pin numbers for the limit switches and motor control
const int switch1Pin = 1;        // Limit switch 1 on conveyor
const int switch2Pin = 0;        // Limit switch 2 on conveyor
const int switch3Pin = 2;        // Limit switch 3 on conveyor
const int switch4Pin = 3;        // Limit switch 4 on conveyor
const int plateSwitchPin = 4;    // Limit switch on the plate
const int robotArmLed1Pin = 7;   // Output LED for Robot Arm 1
const int robotArmLed2Pin = 8;   // Output LED for Robot Arm 2
const int rcCarLedPin = 9;       // Output LED for RC Car
const int extraSwitch1Pin = 5;  // Additional limit switch 1
const int extraSwitch2Pin = 6;  // Additional limit switch 2
const int dirPin = 11;           // Direction pin for A4988
const int stepPin = 10;          // Step pin for A4988
const int enablePin = A0;        // Enable pin for A4988

// Define stepper motor parameters
AccelStepper stepperMotor(AccelStepper::DRIVER, stepPin, dirPin);  // motor control pins

void setup() {
  // Set the limit switch pins as inputs
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(switch3Pin, INPUT);
  pinMode(switch4Pin, INPUT);
  pinMode(plateSwitchPin, INPUT);
  pinMode(extraSwitch1Pin, INPUT);
  pinMode(extraSwitch2Pin, INPUT);

  // Set the output LED pins
  pinMode(robotArmLed1Pin, OUTPUT);
  pinMode(robotArmLed2Pin, OUTPUT);
  pinMode(rcCarLedPin, OUTPUT);

  // Set up A4988 motor driver pins
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
 // pinMode(enablePin, OUTPUT);

  // Enable the A4988 driver
//  digitalWrite(enablePin, LOW);

  // Initialize the AccelStepper library
  stepperMotor.setMaxSpeed(100);
  stepperMotor.setAcceleration(50);

  // Turn off all LEDs initially
  digitalWrite(robotArmLed1Pin, LOW);
  digitalWrite(robotArmLed2Pin, LOW);
  digitalWrite(rcCarLedPin, LOW);
}

void loop() {
    // Read the state of the limit switches
    int switch1State = digitalRead(switch1Pin);
    int switch2State = digitalRead(switch2Pin);
    int switch3State = digitalRead(switch3Pin);
    int switch4State = digitalRead(switch4Pin);
    int plateSwitchState = digitalRead(plateSwitchPin);
    int extraSwitch1State = digitalRead(extraSwitch1Pin);
    int extraSwitch2State = digitalRead(extraSwitch2Pin);

    // Move conveyor backward until switch1 is pressed
    while (switch1State == LOW) {
      stepperMotor.moveTo(stepperMotor.currentPosition() - 1);
      stepperMotor.run();
      switch1State = digitalRead(switch1Pin); // Update the state of switch1
      delay(10);
    }

    // Stop the motor and turn on RC Car LED when switch1 is pressed
    stepperMotor.stop();
    digitalWrite(rcCarLedPin, HIGH);
    delay(1000);
    digitalWrite(rcCarLedPin, LOW);
    // Wait for the user to press plate switch to move the conveyor forward
    while (plateSwitchState == LOW) {
      plateSwitchState = digitalRead(plateSwitchPin);
      delay(10);
    }

    // Move conveyor forward until switch2 is pressed
    while (switch2State == LOW) {
      stepperMotor.moveTo(stepperMotor.currentPosition() + 1);
      stepperMotor.run();
      switch2State = digitalRead(switch2Pin);
      delay(10);
    }

    // Stop the motor and turn on Robot Arm LED 1 when switch2 is pressed
    stepperMotor.stop();
    digitalWrite(robotArmLed1Pin, HIGH);
     while (extraSwitch1State == LOW)
     {
      extraSwitch1State = digitalRead(extraSwitch1Pin);
     }
      digitalWrite(robotArmLed1Pin, LOW);

      switch3State = digitalRead(switch3Pin);
      //  Wait for the user to press extraSwitch1 to move the conveyor forward
      while (switch3State==LOW) 
     {
      stepperMotor.moveTo(stepperMotor.currentPosition() + 1);
      stepperMotor.run();
      switch3State = digitalRead(switch3Pin);
      delay(10);  
      }

    // Stop the motor and turn on Robot Arm LED 2 when switch4 is pressed
    stepperMotor.stop();
    digitalWrite(robotArmLed2Pin, HIGH);
    while(extraSwitch2State == LOW)
    {
    extraSwitch2State = digitalRead(extraSwitch2Pin);
    }
    digitalWrite(robotArmLed2Pin, LOW);

    switch4State = digitalRead(switch4Pin);
   // Wait for the user to press extraSwitch2 to move the conveyor forward
    while (switch4State == LOW) {
      stepperMotor.moveTo(stepperMotor.currentPosition() + 1);
      stepperMotor.run();
      switch4State = digitalRead(switch4Pin);
      delay(10);
    }
  stepperMotor.stop();
}
