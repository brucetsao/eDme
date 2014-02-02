/*
使用for迴圈列印一個數字的各種格式。
*/
int x = 0;    // 定義一個變數並賦值
 
void setup() {
  Serial.begin(9600);      // 打開串口傳輸，並設置串列傳輸速率為9600
}
 
void loop() {
  ///列印標籤
  Serial.print("NO FORMAT");       // 列印一個標籤
  Serial.print("\t");              // 列印一個轉義字元
 
  Serial.print("DEC");  
  Serial.print("\t");      
 
  Serial.print("HEX"); 
  Serial.print("\t");   
 
  Serial.print("OCT");
  Serial.print("\t");
 
  Serial.print("BIN");
  Serial.print("\t"); 
 
  for(x=0; x< 64; x++){    // 列印ASCII碼表的一部分, 修改它的格式得到需要的內容
 
    //  列印多種格式：
    Serial.print(x);       // 以十進位格式將x列印輸出 - 與 "DEC"相同
    Serial.print("\t");    // 橫向跳格
 
    Serial.print(x, DEC);  // 以十進位格式將x列印輸出
    Serial.print("\t");    // 橫向跳格
 
    Serial.print(x, HEX);  // 以十六進位格式列印輸出
    Serial.print("\t");    // 橫向跳格
 
    Serial.print(x, OCT);  // 以八進制格式列印輸出
    Serial.print("\t");    // 橫向跳格
 
    Serial.println(x, BIN);  // 以二進位格式列印輸出
    //                             然後用 "println"列印一個回車
    delay(200);            // 延時200ms
  }
  Serial.println("");      // 列印一個空字元，並自動換行
}
