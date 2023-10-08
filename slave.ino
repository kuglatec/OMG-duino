#include <Wire.h> // Include the Wire library for I2C communication
#include <Keyboard.h> // Include the Keyboard library for simulating keyboard inputs

void setup() {
  Wire.begin(9); // Initialize I2C communication as a slave with the device address 9
  Serial.begin(9600); // Start serial communication for debugging
  Keyboard.begin(); // Initialize the Keyboard library
  Wire.onReceive(receiveEvent); // Set up an event handler for I2C data reception
}

void loop() {
  // The loop is intentionally left empty because the program mainly responds to I2C data events.
}

void receiveEvent(int howmany) {
  byte asciiArray[howmany];

  // Read the incoming I2C data and store it in the asciiArray
  for (int i = 0; i < howmany; i++) {
    asciiArray[i] = Wire.read();
  }

  int arrayLength = sizeof(asciiArray) / sizeof(asciiArray[0]);
  String reversedString = "";

  // Convert the received ASCII data into a string
  for (int i = 0; i < arrayLength; i++) {
    char character = char(asciiArray[i]);
    reversedString += character;
  }

  // Check if the received string is equal to "(run)"
  if (reversedString == "(run)") {
    // Simulate pressing the Windows key (KEY_LEFT_GUI) and 'r' key to open the "Run" dialog
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(100); // Delay for a brief moment to ensure the "Run" dialog is opened
    Keyboard.releaseAll(); // Release all keyboard keys
  } else {
    // Type the received string as keyboard input
    Keyboard.println(reversedString);
  }
}
