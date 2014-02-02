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
  int tempvalue = 0 ;
  tempvalue = US100_TEMP_ultrasonic() ;
    lcd.setCursor(1,1);
      lcd.print("DN:          "); 
    lcd.setCursor(4,1);
  lcd.print(tempvalue); 
  // now result is printed on Serial COnsole
  Serial.print("UltraSonice Temporature Detecting is :") ;
  Serial.println(tempvalue);
  delay(200);  

}
int US100_TEMP_ultrasonic()
{
  int Temperature45 = 0;

  Serial1.flush(); // Clear TX1/RX1 Data Buffer 
  Serial1.write(0x50); // Send byte 0X55，Activate US-100 to start detect temporature   delay(500); // delay 500 microsecond
  
    if(Serial1.available() >= 1) // start receive data when unreceived buffer bytes >= 1 bytes
  {
        Temperature45 = Serial1.read(); //reac US-100 result of detecting temporature
        if ((Temperature45 > 1) && (Temperature45 < 130)) //verify valid value between  1 ~130
        {
        Temperature45 -= 45; // minus 45 for right values
        Serial.print("Detect Temperature is: "); //OUTPUT Value to Serial Monitor
        Serial.print(Temperature45, DEC); //OUTPUT Value to Serial Monitor
        Serial.println(" Degree Centigrade."); //OUTPUT Value to Serial Monitor
        } 
}
  delay(500); //Delay 500 ms
  return (Temperature45) ;
}

