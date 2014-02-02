/* @file CustomKeypad.pde
|| @version 1.0
|| @original author Alexander Brevig
|| @originalcontact alexanderbrevig@gmail.com
||  Author Bruce modified from keypad library  examples download from http://playground.arduino.cc/Code/Keypad#Download @ keypad,zip 
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {31, 33, 35, 37}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
//Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
Keypad customKeypad =  Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
byte ledPin = 13; 
 boolean blink = false ;
 
 
void setup(){
  Serial.begin(9600);
  Serial.println("program start here");
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
   digitalWrite(ledPin, HIGH);   // sets the LED on
   customKeypad.addEventListener(keypadEvent); //add an event listener for this keypad

}
 void loop(){
   char key = customKeypad.getKey();

   if (key) {
     Serial.println(key);
   }
   if (blink){
     digitalWrite(ledPin,!digitalRead(ledPin));
     delay(100);
   }
}

//take care of some special events
void keypadEvent(KeypadEvent key){
   switch (customKeypad.getState()){
     case PRESSED:
       switch (key){
         case '#': digitalWrite(ledPin,!digitalRead(ledPin)); break;
         case '*': 
           digitalWrite(ledPin,!digitalRead(ledPin));
         break;
       }
     break;
     case RELEASED:
       switch (key){
         case '*': 
           digitalWrite(ledPin,!digitalRead(ledPin));
           blink = false;
         break;
       }
     break;
     case HOLD:
       switch (key){
         case '*': blink = true; break;
       }
     break;
   }
}
