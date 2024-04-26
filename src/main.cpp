/*#include "BleGamepad.h"     // Include the BleGamepad library

// Define button GPIO pins
const uint8_t Red = 0;
const uint8_t Green = 1;
const uint8_t Yellow = 2;
const uint8_t Blue = 3;
const uint8_t Orange = 4;
const uint8_t Strum = 5;
const uint8_t Start= 6;
const uint8_t LED_PIN = 21;

// Initialize BleGamepad instance
BleGamepad gamepad("ESP32 Gamepad", "Your Manufacturer", 100);

void setup() {
  Serial.begin(9600);
  gamepad.begin();  // Begin BLE gamepad
  // Set GPIO pins as input with pull-down resistors
  pinMode(Red, INPUT_PULLUP);
  pinMode(Green, INPUT_PULLUP);
  pinMode(Yellow, INPUT_PULLUP);
  pinMode(Blue, INPUT_PULLUP);
  pinMode(Orange, INPUT_PULLUP);
  pinMode(Strum, INPUT_PULLUP);
  pinMode(Start, INPUT_PULLUP);
}

void loop() {
  //delay(10);
  gamepad.sendReport();  // Send gamepad report

  // Example of handling button presses and releases
  if (digitalRead(Red) == LOW) {
      // Handle button press
       Serial.println("Red button pressed");
      digitalWrite(LED_PIN, HIGH);
      gamepad.press(BUTTON_1);
  } else {
      // Handle button release
      digitalWrite(LED_PIN, LOW);
      gamepad.release(BUTTON_1);
  }

  if (digitalRead(Green) == LOW) {
      // Handle button press
      digitalWrite(LED_PIN, HIGH);
       Serial.println("Green button pressed");
      gamepad.press(BUTTON_2);
  } else {
      // Handle button release
      digitalWrite(LED_PIN, LOW);
      gamepad.release(BUTTON_2);
  }

  if (digitalRead(Yellow) == LOW) {
      // Handle button press
      digitalWrite(LED_PIN, HIGH);
       Serial.println("Yellow button pressed");
      gamepad.press(BUTTON_3);
  } else {
      // Handle button release
      digitalWrite(LED_PIN, LOW);
      gamepad.release(BUTTON_3);
  }
  if (digitalRead(Blue) == LOW) {
      // Handle button press
      digitalWrite(LED_PIN, HIGH);
      Serial.println("Blue button pressed");
      gamepad.press(BUTTON_4);
  } else {
      // Handle button release
      digitalWrite(LED_PIN, LOW);
      gamepad.release(BUTTON_4);
  }

  if (digitalRead(Orange) == LOW) {
      // Handle button press
      digitalWrite(LED_PIN, HIGH);
       Serial.println("Orange button pressed");
      gamepad.press(BUTTON_5);
  } else {
      // Handle button release
      digitalWrite(LED_PIN, LOW);
      gamepad.release(BUTTON_5);
  }
  if (digitalRead(Strum) == LOW) {
      // Handle button press
      digitalWrite(LED_PIN, HIGH);
       Serial.println("Strum button pressed");
      gamepad.press(BUTTON_6);
  } else {
      // Handle button release
      digitalWrite(LED_PIN, LOW);
      gamepad.release(BUTTON_6);
  }
  if (digitalRead(Start) == LOW) {
      // Handle button press
      digitalWrite(LED_PIN, HIGH);
      Serial.println("Start button pressed");
      gamepad.press(BUTTON_7);
  } else {
      // Handle button release
      digitalWrite(LED_PIN, LOW);
      gamepad.release(BUTTON_7);
  }
}*/
/*
 * This code programs a number of pins on an ESP32 as buttons on a BLE gamepad
 *
 * It uses arrays to cut down on code
 *
 * Before using, adjust the numOfButtons, buttonPins and physicalButtons to suit your senario
 *
 */

#include <Arduino.h>
#include <BleGamepad.h> // https://github.com/lemmingDev/ESP32-BLE-Gamepad

BleGamepad bleGamepad;

#define numOfButtons 8

byte previousButtonStates[numOfButtons];
byte currentButtonStates[numOfButtons];
byte buttonPins[numOfButtons] = {0, 1, 2, 3, 4, 5, 6, 7};
byte physicalButtons[numOfButtons] = {1, 2, 3, 4, 5, 6, 7, 8};

void setup()
{
    for (byte currentPinIndex = 0; currentPinIndex < numOfButtons; currentPinIndex++)
    {
        pinMode(buttonPins[currentPinIndex], INPUT_PULLUP);
        previousButtonStates[currentPinIndex] = HIGH;
        currentButtonStates[currentPinIndex] = HIGH;
    }

    BleGamepadConfiguration bleGamepadConfig;
    bleGamepadConfig.setAutoReport(false);
    bleGamepadConfig.setButtonCount(numOfButtons);
    bleGamepad.begin(&bleGamepadConfig);

    // changing bleGamepadConfig after the begin function has no effect, unless you call the begin function again
}

void loop()
{
    if (bleGamepad.isConnected())
    {
        for (byte currentIndex = 0; currentIndex < numOfButtons; currentIndex++)
        {
            currentButtonStates[currentIndex] = digitalRead(buttonPins[currentIndex]);

            if (currentButtonStates[currentIndex] != previousButtonStates[currentIndex])
            {
                if (currentButtonStates[currentIndex] == LOW)
                {
                    bleGamepad.press(physicalButtons[currentIndex]);
                }
                else
                {
                    bleGamepad.release(physicalButtons[currentIndex]);
                }
            }
        }

        if (currentButtonStates != previousButtonStates)
        {
            for (byte currentIndex = 0; currentIndex < numOfButtons; currentIndex++)
            {
                previousButtonStates[currentIndex] = currentButtonStates[currentIndex];
            }

            bleGamepad.sendReport();
        }

        delay(5);
    }
}