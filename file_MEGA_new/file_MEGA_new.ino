#include <Wire.h>          
#include "Timer.h"      
#include <LiquidCrystal.h>      
#define Slave 0x04 // Slave 주소

const unsigned long PERIOD1 = 1000;
LiquidCrystal lcd(2,3,4,5,6,7); 

int box_1 = 22;
int box_2 = 23;
int box_3 = 24;
int box_4 = 25;
int box_5 = 26;
int box_6 = 27;

int button_up = 9;
int button_down = 10;
int button_ok = 11;

int count = 0;
int count_time = 0;
int Time = 0;
int page = 0;
int mode = 20;
Timer t;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  
  pinMode(box_1, OUTPUT);
  pinMode(box_2, OUTPUT);
  pinMode(box_3, OUTPUT);
  pinMode(box_4, OUTPUT);
  pinMode(box_5, OUTPUT);
  pinMode(box_6, OUTPUT);

  pinMode(button_up, INPUT_PULLUP);
  pinMode(button_down, INPUT_PULLUP);
  pinMode(button_ok, INPUT_PULLUP);
  
  lcd.begin(16,2);
  
  lcd.setCursor(0, 0);
  lcd.print("Hello World");
  delay(1000);
  
  lcd.clear();
  page_0();
}

void loop() {
  switch(page){
     case 0 : page_0(); break;
     case 1 : page_1(); break;
     case 2 : page_2(); break;
   }
}

void page_0(){
  while(digitalRead(button_ok) == HIGH){
    lcd.setCursor(0, 0);  
    lcd.print("Enter the Locker to be used :");
       
    lcd.setCursor(0, 1);                         
    lcd.print("Locker : "); lcd.print(count);


    if (digitalRead(button_up) == LOW){ count ++; delay(200);}
    if (digitalRead(button_up) == HIGH){}

    if (digitalRead(button_down) == LOW && count != 0){ count --; delay(200);}
    if (digitalRead(button_down) == HIGH){}

    if (digitalRead(button_ok) == LOW && count != 0 ){  page_1(); delay(200); }
    if (digitalRead(button_ok) == HIGH){}
  }  
}

void page_1(){
  delay(500);
     while(1){
      if(mode%2 == 1){
        lcd.setCursor(0, 0);                         
        lcd.print(">  Perfect mode       ");
        lcd.setCursor(0, 1);  
        lcd.print("   Quick mode            ");
        lcd.display();
        count_time = 9;
      }
      if(mode%2 == 0){
        lcd.setCursor(0, 0);                         
        lcd.print("   Perfect mode        ");
        lcd.setCursor(0, 1);  
        lcd.print(">  Quick mode            ");
        lcd.display();
        count_time = 3;
      }
      
      if (digitalRead(button_up) == LOW){ mode = mode+1; delay(200); }
      if (digitalRead(button_up) == HIGH){}

      if (digitalRead(button_down) == LOW){mode = mode-1; delay(200); }
      if (digitalRead(button_down) == HIGH){}

      if (digitalRead(button_ok) == LOW && count_time != 0){
        //if(mode%2 == 1){ count_time = 3; } //Perfect mode
        //if(mode%2 == 0){ count_time = 9; } //Quick mode
        page_2(); 
        delay(200);
      }
       if (digitalRead(button_ok) == HIGH){}
      }
}

void page_2(){
    while(1){
      Wire.beginTransmission(Slave); // Slave로 데이터 전송 시작

      if(count == 1){
        Serial.print("1번박스 "); Serial.print(count_time); Serial.println(" 분 작동시작");
        if(count_time == 3){
          Wire.write("a"); // 1번 락커
          Wire.write("-");
          Wire.write("g");
          Wire.endTransmission();
        } if(count_time == 9){
          Wire.write("a"); // 1번 락커
          Wire.write("-");
          Wire.write("i");
          Wire.endTransmission();
        }
      }

      if(count == 2){
        Serial.print("2번박스 "); Serial.print(count_time); Serial.println(" 분 작동시작");
        if(count_time == 3){
          Wire.write("b"); // 2번 락커
          Wire.write("-");
          Wire.write("g");
          Wire.endTransmission();
        } if(count_time == 9){
          Wire.write("b"); // 2번 락커
          Wire.write("-");
          Wire.write("i");
          Wire.endTransmission();
        }
      }


     if(count == 3){
      Serial.print("3번박스 "); Serial.print(count_time); Serial.println(" 분 작동시작");
        if(count_time == 3){
          Wire.write("c"); // 3번 락커
          Wire.write("-");
          Wire.write("g");
          Wire.endTransmission();
        } if(count_time == 9){
          Wire.write("c"); // 3번 락커
          Wire.write("-");
          Wire.write("i");
          Wire.endTransmission();
        }
      }

      if(count == 4){
          Serial.print("4번박스 "); Serial.print(count_time); Serial.println(" 분 작동시작");
        if(count_time == 3){
          Wire.write("d"); // 4번 락커
          Wire.write("-");
          Wire.write("g");
          Wire.endTransmission();
        } if(count_time == 9){
          Wire.write("d"); // 4번 락커
          Wire.write("-");
          Wire.write("i");
          Wire.endTransmission();
        }
      }

      if(count == 5){
          Serial.print("5번박스 "); Serial.print(count_time); Serial.println(" 분 작동시작");
        if(count_time == 3){
          Wire.write("e"); // 5번 락커
          Wire.write("-");
          Wire.write("g");
          Wire.endTransmission();
        } if(count_time == 9){
          Wire.write("e"); // 5번 락커
          Wire.write("-");
          Wire.write("i");
          Wire.endTransmission();
        }
      }

      if(count == 6){
           Serial.print("6번박스 "); Serial.print(count_time); Serial.println(" 분 작동시작");
        if(count_time == 3){
          Wire.write("f"); // 6번 락커
          Wire.write("-");
          Wire.write("g");
          Wire.endTransmission();
        } if(count_time == 9){
          Wire.write("f"); // 6번 락커
          Wire.write("-");
          Wire.write("i");
          Wire.endTransmission();
        }
      }

         lcd.setCursor(0, 0);                         
         lcd.print("Start Work!!           ");
     
         lcd.setCursor(0, 1);   
         lcd.print("[PUSH THE RESET]");
         delay(1000);
         if (digitalRead(button_ok) == LOW ){ break; }  //아두이노 자체를 초기화시키기
         if (digitalRead(button_ok) == HIGH){}
      }
      page_0();
      page = 0;
}
