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

#include <Keypad.h>
#include <LiquidCrystal.h>
#define EchoPin  12         
#define TrigPin  11         

LiquidCrystal lcd(5,6,7,38,40,42,44);   //ok

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

int devicemode = 1 ;
double distance1d = 0 ;
double distance2d = 0 ;
double distance3d = 0 ;

//initialize an instance of class NewKeypad
//Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
Keypad customKeypad =  Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 



void setup(){
    pinMode(EchoPin, INPUT);                    //Set EchoPin as input, to receive measure result from US-020
    pinMode(TrigPin, OUTPUT);                   //Set TrigPin as output, used to send high pusle to trig measurement (>10us)

  Serial.begin(9600);
  Serial.println("program start here");
 
lcd.begin(20, 4);
// 設定 LCD 的行列數目 (16 x 2)  16　行2　列
   lcd.setCursor(0,0);
  // 列印 "Hello World" 訊息到 LCD 上 
  Serial.println("Ultrasonic sensor detecting...");

}
  
void loop(){
  switch (devicemode)
  {
    case 1:
      distance1d = HC04_ultrasonic() ;
      break ;
      
    case 2:
      distance2d = HC04_ultrasonic() ;
      break ;
      
    case 3:
      distance3d = HC04_ultrasonic() ;
      break ;
      
  }
  
    showdistance();

        // now result is printed on Serial COnsole
          Serial.print("UltraSonice DIstance1 is :") ;
         Serial.println(distance1d);
          Serial.print("UltraSonice DIstance2 is :") ;
         Serial.println(distance2d);
          Serial.print("UltraSonice DIstance3 is :") ;
         Serial.println(distance3d);
          Serial.print("UltraSonice Area is :") ;
         Serial.println(distance1d * distance2d);
          Serial.print("UltraSonice Cubic is :") ;
         Serial.println(distance1d * distance2d * distance3d);
    delay(200);  

}
void showdistance()
{
  lcd.setCursor(0,0);
  lcd.print("Distance D1:"); 
  lcd.print(distance1d); 
  lcd.setCursor(0,1);
  lcd.print("Distance D2:"); 
  lcd.print(distance2d); 
  lcd.setCursor(0,2);
  lcd.print("Distance D3:"); 
  lcd.print(distance3d); 
  lcd.setCursor(0,3);
  lcd.print(""); 
  lcd.print(distance1d ); 
  lcd.print(" "); 
  lcd.print(distance1d * distance2d ); 
  lcd.print(" "); 
  lcd.print(distance1d * distance2d*distance3d); 
  
}  

long getpadnumber()
{
   const int maxstring = 8;
  char getinputnumber[maxstring] ;
  char InputKeyString = 0x00;
   int  stringpz = 0;
   
  while (stringpz < maxstring)
  {
    InputKeyString = getpadnumberchar();
     if (InputKeyString != 0x00)
     {
       if (InputKeyString != 0x13)
         {
           getinputnumber[stringpz] = InputKeyString ;
           stringpz ++ ;
         }
         else
         {
           break ;
         }
     }
}  
stringpz ++;
getinputnumber[stringpz] = 0x00 ;
return (atol(getinputnumber) );
}

char getpadnumberchar()
{
  char InputKey;
  char checkey = 0x00;  
   
  while (checkey == 0x00)
    {
      InputKey = customKeypad.getKey();
      if (InputKey != 0x00 )
        {
        checkey = cmppadnumberchar(InputKey) ;
//      Serial.print("in  getnumberchar for loop  is :") ;
//          Serial.println(InputKey,HEX) ;
        }
      /*  else
        {
          Serial.print("in  getnumberchar and not if  for loop  is :") ;
          Serial.println(InputKey,HEX) ;
        }
        */
        delay(50);
    }  
  //  Serial.print("exit  getnumberchar is :") ;
  //  Serial.println(checkey,HEX) ;
   return (checkey); 
}


char cmppadnumberchar(char cmpchar)
{
  const int cmpcharsize = 11 ;
char tennumber[cmpcharsize] = {'0','1','2','3','4','5','6','7','8','9','#'} ;
//char retchar = "" ;  
 for(int i  = 0; i< cmpcharsize; i++)
   {
    if (cmpchar == tennumber[i] )
      {
        if (cmpchar == '#')
          {
               return  (0x13) ;
          }
          else
          {
              return  (cmpchar) ;
          }
      }
        
   }
  return  (0x00) ;
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

char getpadfunctionchar()
{
  char InputKey;
  char checkey = 0x00;  
   
      InputKey = customKeypad.getKey();
        delay(40);
      if (InputKey != 0x00 )
        {
            checkey = cmppadfunctionchar(InputKey) ;
        }
   return (checkey); 
}


char cmppadfunctionchar(char cmpchar)
{
  const int cmpcharsize = 5 ;
char tennumber[cmpcharsize] = {'A','B','C','D','*'} ;
//char retchar = "" ;  
 for(int i  = 0; i< cmpcharsize; i++)
   {
    if (cmpchar == tennumber[i] )
      {
              return  (cmpchar) ;
      }
        
   }
  return  (0x00) ;
}  

