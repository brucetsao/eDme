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
  distanceno = SFR04_ultrasonic() ;
    lcd.setCursor(1,1);
      lcd.print("DN:"); 
      lcd.print(distanceno); 
        // now result is printed on Serial COnsole
          Serial.print("UltraSonice DIstance Detecting is :") ;
         Serial.println(distanceno);
    delay(200);  

}

unsigned long SFR04_ultrasonic()
{
  long duration, inches, cm;
  
  
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  duration = pulseIn(EchoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  return (cm) ;
}
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

