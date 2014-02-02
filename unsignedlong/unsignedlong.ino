unsigned long time;
 
void setup()
{
     Serial.begin(9600);
}
 
void loop()
{
  Serial.print("Time: ");
  time = millis();
  //程式開始後一直列印時間
  Serial.println(time);
  //等待一秒鐘，以免發送大量的資料
  delay(1000);
}
