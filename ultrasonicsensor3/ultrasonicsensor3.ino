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
#define EchoPin  12           // connect Pin 2(Arduino digital io) to Echo at US-020
#define TrigPin  11          // connect Pin 3(Arduino digital io) to Trig at US-020



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


//initialize an instance of class NewKeypad
//Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
Keypad customKeypad =  Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 



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

