//
#include <usToDE.h> //only needed for german keyboard translation, remove when US keyboard and change #139 ff
#include <Keyboard.h>
#include <Mouse.h>
#include <Encoder.h>

//BUTTONS FOR ARDUINO Pro Micro
int buttonPin1 = 7;//First button Rotary encoder 1 int
int buttonPin2 = 4;//Second button Rotary encoder 2 int
int buttonPin4 = 10;//Stand alone button 1 int
int buttonPin5 = 16;//Stand alone button 2 int
int buttonPin6 = 14;//Stand alone button 3 int
int buttonPin7 = 15;//Stand alone button 4 int
int previousButtonState = HIGH;

//DECODER DEFS
#define ENCODER_R0  9
#define ENCODER_R1  8
#define ENCODER_L0  6
#define ENCODER_L1  5

Encoder knobLeft(ENCODER_L0,ENCODER_L1);
Encoder knobRight(ENCODER_R1,ENCODER_R0);
char newLeftValue=0;

void setup() {
  pinMode(buttonPin4, INPUT);  //Stand alone button 1
  digitalWrite(buttonPin4, HIGH);  // Pull stand alone button 1 high

  pinMode(buttonPin5, INPUT);  //Stand alone button 2
  digitalWrite(buttonPin5, HIGH);  // Pull stand alone button 2 high

  pinMode(buttonPin6, INPUT);  //Stand alone button 3
  digitalWrite(buttonPin6, HIGH);  // Pull stand alone button 3 high

  pinMode(buttonPin7, INPUT);  //Stand alone button 4
  digitalWrite(buttonPin7, HIGH);  // Pull stand alone button 4 high

  pinMode(buttonPin1, INPUT);  //First Button Encoder 1
  digitalWrite(buttonPin1, HIGH);  // Pull the Button Encoder 1 button high

  pinMode(buttonPin2, INPUT);  //Second Button Encoder 2
  digitalWrite(buttonPin2, HIGH);  // Pull the button Button Encoder 1 high

  Serial.begin(9600);
  Keyboard.begin();//Init Keyboard
}
void loop() {
  //ENCODER BUTTON FUNTIONS

  //FIRST encoder button 1 for CENTER WATERFALL
  if (digitalRead(buttonPin1) == LOW)  // if the button goes high
  {
    Keyboard.press('V');
    delay(300);
    Serial.println ("Pressed V");
    Keyboard.releaseAll();
  }

//  //Second encoder button 2 for LO Lock
  if (digitalRead(buttonPin2) == LOW)  // if the button goes high
  {
    Keyboard.press('K');
    delay(300);
    Serial.println ("Pressed K");
    Keyboard.releaseAll();
  }
//
//  //STAND ALONE BUTTONS 1-4
//
//  //FIRST STAND ALONE BUTTON (MODE AM)
  if (digitalRead(buttonPin4) == HIGH)  // if the button goes high
  {
    Keyboard.press('A');
    delay(300);
    Serial.println ("Pressed A");
    Keyboard.releaseAll();
  }
//
//  //SECOND STAND ALONE BUTTON (MODE USB)
  if (digitalRead(buttonPin5) == HIGH)  // if the button goes high
  {
    Keyboard.press('U');
        delay(300);
    Serial.println ("Pressed U");
    Keyboard.releaseAll();
  }
//
//  //THIRD STAND ALONE BUTTON (MODE LSB)
  if (digitalRead(buttonPin6) == HIGH)  // if the button goes high
  {
    Keyboard.press('L');
    delay(300);
    Serial.println ("Pressed L");
    Keyboard.releaseAll();
  }
//
//  //FORTH STAND ALONE BUTTON (MODE FM)
  if (digitalRead(buttonPin7) == HIGH)  // if the button goes high
  {
    Keyboard.press('F');
    delay(300);
    Serial.println ("Pressed F");
    Keyboard.releaseAll();
  }

//  ENCODER FUNTIONS
//  with encoder.h library

  char leftValue=0,rightValue=0;
  leftValue = knobLeft.read();
  rightValue = knobRight.read();

  // Right Encoder
  if(rightValue > 3)
  {
    Serial.println("Tune up");
    knobRight.write(0);
    Keyboard.write(KEY_UP_ARROW);
    delay(100);
    //Keyboard.releaseAll();
  }
  else if(rightValue < -3)
  {
    Serial.println("Tune down");
    knobRight.write(0);
    Keyboard.write(KEY_DOWN_ARROW);
    delay(100);
    //Keyboard.releaseAll();
   }
  
 // Left Encoder
  if(newLeftValue != leftValue)
  {
  if(leftValue > 3)
  {
    Serial.println("Plus char");
    knobLeft.write(0);
    unsigned char inChar = ('+'); //remove when US keyboard
    unsigned char key = (usToDE[inChar]); //remove when US keyboard
    Keyboard.write(key); //send ('+') when US keyboard
    delay(100);
  }
  else if(leftValue < -3)
  {
    Serial.println("Minus char");
     knobLeft.write(0);
    unsigned char inChar = ('-'); //remove when US keyboard
    unsigned char key = (usToDE[inChar]); //remove when US keyboard
    Keyboard.write(key); //send ('-') when US keyboard
    delay(100);
  }
 }
    newLeftValue = leftValue;
  }
