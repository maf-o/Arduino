//  SNES Controller -> USB Keyboard
//  
//  A simple program which converts the input of the SNES controller, to that of a USB keyboard.
//  
//  Please Note:
//  
//  REQUIRES at least ARDUINO LEONARDO - as uses 'Keyboard' libraries unavaliable to older versions of the board.
//  
//  Settings:
//  
//  Please use the below to select the pin that you are to be using, and the key that you would like to be output 
//  from the keyboard when that button is pressed.
//
// 
//
//	     +----> 5V                    +-----------------------\
//	     |                          7 | o  o  o  o |  x  x  o  | 1
// 5 +---------+  7                       +-----------------------/
//   | x  x  o   \                          |  |  |  |          |
//   | o  o  o  o |                         |  |  |  |          +-> Ground
// 4 +------------+ 1                       |  |  |  +------------> Data
//     |  |  |  |                           |  |  +---------------> Latch
//     |  |  |  +-> Ground                  |  +------------------> Clock
//     |  |  +----> Clock                   +---------------------> 5V (auch mit 3V3 gesehen)
//     |  +-------> Latch
//     +----------> Data
//
//  Clock Pin:
const int dataClockPin = 16;
//  Latch Pin:
const int dataLatchPin = 15;
//  Data Pin (Input) :
const int serialDataPin = 14;

// USB Keyboard Output:
//
// Please note if you wish to use any special keys, refer to:
// http://arduino.cc/en/Reference/KeyboardModifiers
// 
// A Keyboard Output:
const char aOutput = 'l';
// B Keyboard Output:
const char bOutput = 'k';
// X Keyboard Output:
const char xOutput = 'o';
// Y Keyboard Output:
const char yOutput = 'i';
// Start Keyboard Output:
const char startOutput = 'j';
// Select Keyboard Output:
const char selectOutput = 'u';
// L Keyboard Output:
const char lOutput = 'y';
// R Keyboard Output:
const char rOutput = 'h';
// Up Keyboard Output:
const char upOutput = 'w';
// Down Keyboard Output:
const char downOutput = 's';
// Left Keyboard Output:
const char leftOutput = 'a';
// Right Keyboard Output:
const char rightOutput = 'd';


int dataLatchDelay = 12;
int betweenButtonDelay = 2;

void setup() {
    // Data Clock
    pinMode(dataClockPin, OUTPUT);
    // Data Latch
    pinMode(dataLatchPin, OUTPUT);
    // Serial Data (Incoming)
    pinMode(serialDataPin, INPUT);

    // Start USB keyboard output
    Keyboard.begin();
}

void loop() {
    
    // Data Latch HIGH
    digitalWrite(dataLatchPin, HIGH);
    delayMicroseconds(dataLatchDelay);
    
    // Data Latch LOW
    digitalWrite(dataLatchPin, LOW);
    delayMicroseconds(betweenButtonDelay);
    
    // Read B - it's a special case
    !digitalRead(serialDataPin) ? Keyboard.press(bOutput) : Keyboard.release(bOutput);
    
    // Read remaining buttons
    readButtonNormal(yOutput);
    readButtonNormal(selectOutput);
    readButtonNormal(startOutput);
    readButtonNormal(upOutput);
    readButtonNormal(downOutput);
    readButtonNormal(leftOutput);
    readButtonNormal(rightOutput);
    readButtonNormal(aOutput);
    readButtonNormal(xOutput);
    readButtonNormal(lOutput);
    readButtonNormal(rOutput);
    
    // 4 Serial pulses, never used by Nintendo - but still exist
    readNonExistantButton();
    readNonExistantButton();
    readNonExistantButton();
    readNonExistantButton();
    
}

/*
 
 A function for reading in a particular button, excepts the keyboard output as a parameter

*/
void readButtonNormal(char letterOutput) {
     
    // Push the data clock HIGH
    digitalWrite(dataClockPin, HIGH);
    delayMicroseconds(betweenButtonDelay);
    
    // Data clock LOW
    digitalWrite(dataClockPin, LOW);
    delayMicroseconds(betweenButtonDelay);

    // Read the Serial line and thus the button
    !digitalRead(serialDataPin) ? Keyboard.press(letterOutput) : Keyboard.release(letterOutput);
    
}

/*

  A function for getting through the unused buttons

*/
void readNonExistantButton() {
  
    // Push the data clock HIGH
    digitalWrite(dataClockPin, HIGH);
    delayMicroseconds(betweenButtonDelay);
    
    // Data clock Low
    digitalWrite(dataClockPin, LOW);
    delayMicroseconds(betweenButtonDelay);
    
}
