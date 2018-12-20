//
//The keyboard.h library only supports US ascii characters from 1-127. So for a german keyboard you have to enable the usToDE header file and routine in the code

//#include <usToDE.h> //only needed for german keyboard translation, remove when US keyboard and change #139 ff
#include <Keyboard.h>
#include <Mouse.h>
#include <Encoder.h>

 // Echo keypresses over serial for debug
#define debug true //define false, if you go productive

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
    
    Keyboard.releaseAll();
    if(debug)
    {
    Serial.println ("Pressed V");
    }
  }
//  //Second encoder button 2 for LO Lock
  if (digitalRead(buttonPin2) == LOW)  // if the button goes high
  {
    Keyboard.press('K');
    delay(300);
    Keyboard.releaseAll();
    if(debug)
    {
    Serial.println ("Pressed K");
    }
  }
//
//  //STAND ALONE BUTTONS 1-4
//
//  //FIRST STAND ALONE BUTTON (MODE AM)
  if (digitalRead(buttonPin4) == HIGH)  // if the button goes high
  {
    Keyboard.press('A');
    delay(300);
    Keyboard.releaseAll();
    if(debug)
    {
    Serial.println ("Pressed A");
    }
  }
//
//  //SECOND STAND ALONE BUTTON (MODE USB)
  if (digitalRead(buttonPin5) == HIGH)  // if the button goes high
  {
    Keyboard.press('U');
    delay(300);
    Keyboard.releaseAll();
    if(debug)
    {
    Serial.println ("Pressed U");
    }
  }
//
//  //THIRD STAND ALONE BUTTON (MODE LSB)
  if (digitalRead(buttonPin6) == HIGH)  // if the button goes high
  {
    Keyboard.press('L');
    delay(300);
    Keyboard.releaseAll();
    if(debug)
    {
    Serial.println ("Pressed L");
    }
  }
//
//  //FORTH STAND ALONE BUTTON (MODE FM)
  if (digitalRead(buttonPin7) == HIGH)  // if the button goes high
  {
    Keyboard.press('F');
    delay(300);
    Keyboard.releaseAll();
    if(debug)
    {
    Serial.println ("Pressed F");
    }
  }

//  ENCODER FUNTIONS
//  with encoder.h library

  char leftValue=0,rightValue=0;
  leftValue = knobLeft.read();
  rightValue = knobRight.read();

  // Right Encoder
  if(rightValue > 3)
  {
    knobRight.write(0);
    Keyboard.write(KEY_UP_ARROW);
    delay(100);
    if(debug){
    Serial.println("Tune up");
    }
  }
  else if(rightValue < -3)
  {
    knobRight.write(0);
    Keyboard.write(KEY_DOWN_ARROW);
    delay(100);
    if(debug){
    Serial.println("Tune down");
     }
   }
  
 // Left Encoder
  if(newLeftValue != leftValue)
  {
  if(leftValue > 3)
  {
    knobLeft.write(0);
    unsigned char key = ('+'); //deactivate when DE keyboard and activate the two lines below
//    unsigned char inChar = ('+'); //activate  when DE keyboard
//    unsigned char key = (usToDE[inChar]); //activate when DE keyboard
    Keyboard.write(key); 
    delay(100);
    if(debug){
    Serial.println("Plus Char");
    }
  }
  else if(leftValue < -3)
  {
    knobLeft.write(0);
    unsigned char key=('-');//deactivate when DE keyboard
//    unsigned char inChar = ('-'); //activate when DE keyboard
//    unsigned char key = (usToDE[inChar]); //activate when DE keyboard
    Keyboard.write(key); 
    delay(100);
    if(debug){
    Serial.println("Minus Char");
     }
  }
 }
    newLeftValue = leftValue;
  }
