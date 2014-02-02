/* @file Enhance Keypad use
|| @version 1.0
||  Author Bruce modified from keypad library  examples download from http://playground.arduino.cc/Code/Keypad#Download @ keypad,zip 
*/
/* LiquidCrystal display with:

LiquidCrystal(rs, enable, d4, d5, d6, d7) 
LiquidCrystal(rs, rw, enable, d4, d5, d6, d7) 
LiquidCrystal(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7) 
LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7) 
R/W Pin Read = LOW / Write = HIGH   // if No pin connect RW , please leave R/W Pin for Low State

*/
#include <LiquidCrystal.h>
#define EchoPin  12           // connect Pin 2(Arduino digital io) to Echo at US-020
#define TrigPin  11          // connect Pin 3(Arduino digital io) to Trig at US-020

LiquidCrystal lcd(5,6,7,38,40,42,44);   //ok
void setup(){
    pinMode(EchoPin, INPUT);                    //Set EchoPin as input, to receive measure result from US-020
    pinMode(TrigPin, OUTPUT);                   //Set TrigPin as output, used to send high pusle to trig measurement (>10us)

  Serial.begin(9600);
  Serial.println("program start here");
 
lcd.begin(16, 2);
// 設定 LCD 的行列數目 (16 x 2)  16　行2　列
 lcd.setCursor(0,0);
  // 列印 "Hello World" 訊息到 LCD 上 
lcd.print("UltraSonic"); 
  Serial.println("Ultrasonic sensor detecting...");

}
  
void loop(){
  long distanceno = 0 ;
  distanceno = US100_GPIO_ultrasonic() ;
    lcd.setCursor(1,1);
      lcd.print("DN:          "); 
    lcd.setCursor(4,1);
      lcd.print(distanceno); 
        // now result is printed on Serial COnsole
          Serial.print("UltraSonice DIstance Detecting is :") ;
         Serial.println(distanceno);
    delay(500);  

}

long US100_GPIO_ultrasonic()
{
  unsigned long Len_mm = 0;
  unsigned long Time_Echo_us = 0;
  
//via Trig/Pin Send pulse，activate US-100 modules
digitalWrite(TrigPin, HIGH); //start to send pulse to Trig/Pin 
delayMicroseconds(50); //set pulse width to 50us (>10us)
digitalWrite(TrigPin, LOW); //end send pulse
Time_Echo_us = pulseIn(EchoPin, HIGH); //count US-100 returning pulse width from US-100
Serial.print("get pules is:");
Serial.println(Time_Echo_us);

if((Time_Echo_us < 60000) && (Time_Echo_us > 1))  //Pulse Width valid limited to (1, 60000).
{
// Len_mm = (Time_Echo_us * 0.34mm/us) / 2 (mm)
Len_mm = (Time_Echo_us*34/100)/2; //calculate pulse width 
Serial.print("Present Distance is: ");
Serial.print(Len_mm, DEC); //send result to tx/rx monitor
Serial.println("mm"); 
}  
  return (Len_mm) ;
}

