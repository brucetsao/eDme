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

LiquidCrystal lcd(5,6,7,38,40,42,44);   //ok

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
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
  distanceno = US100_UART_ultrasonic() ;
    lcd.setCursor(1,1);
      lcd.print("DN:          "); 
    lcd.setCursor(4,1);
      lcd.print(distanceno); 
  // now result is printed on Serial COnsole
  Serial.print("UltraSonice DIstance Detecting is :") ;
  Serial.println(distanceno);
  delay(200);  

}
long US100_UART_ultrasonic()
{
  unsigned int HighLen = 0;
  unsigned int LowLen = 0;
  long Len_mm = 0;


  Serial1.flush(); // Clear TX1/RX1 Data Buffer 
  Serial1.write(0x55); // Send byte 0X55，Activate US-100 to start work
  delay(500); // delay 500 microsecond
  Serial.print("in read is :");
  Serial.print(Serial1.available());
      Serial.println(""); 
  if(Serial1.available() >= 2) // start receive data when unreceived buffer bytes >= 2 bytes
  {
    HighLen = Serial1.read(); // Hi byte of Distance
    LowLen = Serial1.read(); // Li byte of Distance
    Serial.print("Hi:");
  Serial.print(HighLen);
    Serial.print("Lo:");
  Serial.print(LowLen);
      Serial.println(""); 

    Len_mm = HighLen*256 + LowLen; //Calculate DIstance from Hi byte & Lo byte
    if((Len_mm > 1) && (Len_mm < 10000)) //validate legal values between 1mm to 10000 mm 之间
    {
      Serial.print("Distance is: "); //Output distance to Serial Monitor
      Serial.print(Len_mm, DEC); //Output Distance value
      Serial.println("mm"); 
    }
  }
  delay(500); //Delay 500 ms
  return (Len_mm) ;
}



