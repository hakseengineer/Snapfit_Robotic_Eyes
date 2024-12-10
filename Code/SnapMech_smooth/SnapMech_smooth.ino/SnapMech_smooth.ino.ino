/********************************************************************************
     Author : Hak Se Engineer
     Date   : 05/12/2024

This code will be used to control Robotic Eyes using Joystick.
*********************************************************************************/

#include <Servo.h>

Servo lookLR;  
Servo lookUD;  
Servo lidBL;  
Servo lidTL;  
Servo lidBR;  
Servo lidTR;  

int BUTPin = 7;
int UDPin = A0;
int LRPin = A1;

int UDState = 90;
int LRState = 90;
int buttonState = 0;
int lidMod = 0;

float prev_UDState = 90.0;
float prev_LRState = 90.0;
float smooth_UDState, smooth_LRState;



void setup() {
  Serial.begin(9600);
  pinMode(BUTPin, INPUT_PULLUP);
  
  lookLR.attach(3);
  lookUD.attach(5);
  lidBL.attach(6);
  lidTL.attach(9);
  lidBR.attach(10);
  lidTR.attach(11);
}

void loop() {

  buttonState =  digitalRead(BUTPin);
  UDState = map(analogRead(UDPin), 0, 1023, 50, 130);
 
  LRState = map(analogRead(LRPin), 0, 1023, 40, 140);  
  
  //Serial.println(buttonState);

/* Below logic will be used to make eye ball transition smooth. */

  smooth_UDState = (UDState * 0.08) + (prev_UDState * 0.92);
  smooth_LRState = (LRState * 0.08) + (prev_LRState * 0.92);

  prev_UDState = smooth_UDState;
  prev_LRState = smooth_LRState;

/* Debug Purpose... */

  Serial.print(UDState);
  Serial.print("  ,  ");
  Serial.print((int)smooth_UDState);
  Serial.print("   :   ");
    Serial.print(LRState);
  Serial.print("  ,  ");
  Serial.println(smooth_LRState);


  lookUD.write((int)smooth_UDState);
  lookLR.write((int)smooth_LRState);
  lidMod = (40 - smooth_UDState)/2;

  if (buttonState == 0){
    lidBL.write(90);    /* Close Bottom Left Eye Lid */
    lidTL.write(90);    /* Close Top Left Eye Lid */
    lidBR.write(90);    /* Close Bottom Right Eye Lid */
    lidTR.write(90);    /* Close Top Left Eye Lid */
  } else {
    lidBL.write(160+lidMod);   /* You can tune up these values as per your setup */
    lidTL.write(70+lidMod);
    lidBR.write(30-lidMod);
    lidTR.write(110-lidMod);
  }

}
