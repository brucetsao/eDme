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
  double distanceno = 0 ;
  distanceno = HC04_ultrasonic() ;
    lcd.setCursor(1,1);
      lcd.print("DN:"); 
      lcd.print(distanceno); 
        // now result is printed on Serial COnsole
          Serial.print("UltraSonice DIstance Detecting is :") ;
         Serial.println(distanceno);
    delay(200);  

}

double HC04_ultrasonic()
{
   double tmp = 0 ;
  double duration, distance;
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0){
    tmp = -1 ;
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println("Out of range");
    Serial.println("--------------");
  }
  else {
        tmp = distance ;
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println("read ok...");
    Serial.println("--------------");
  }
 
  return (tmp);
}

