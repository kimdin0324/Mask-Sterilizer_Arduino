#include <LiquidCrystal.h>      
#include <Wire.h>          
#include "Timer.h"      
#define Slave 0x04 // Slave 주소

LiquidCrystal lcd(2,3,4,5,6,7);  // LCD 핀설정

int box_1 = 22;  // UV 락커 핀설정
int box_2 = 23;  // 이하같음
int box_3 = 24;
int box_4 = 25;
int box_5 = 26;
int box_6 = 27;

int button_up = 9;     // UP버튼 핀설정
int button_down = 10;  // DOWN버튼 핀설정
int button_ok = 11;    // OK버튼 핀설정

int count = 0;       // 락커 번호 설정 변수
int count_time = 0;  // 락커 작동시간 설정 변수
int Time = 0;
int page = 0;    // 페이지 넘기는 변수
int mode = 20;   // 모드 선택시 (mode%2)의 값의 짝,홀로 선택하기 위해

void setup(){
  Serial.begin(9600);
  Wire.begin();    // 우노와 I2C통신을 위한 설정
  
  pinMode(box_1, OUTPUT);  // UV 락커 핀모드 설정
  pinMode(box_2, OUTPUT);  // 이하같음
  pinMode(box_3, OUTPUT);
  pinMode(box_4, OUTPUT);
  pinMode(box_5, OUTPUT);
  pinMode(box_6, OUTPUT);

  pinMode(button_up, INPUT_PULLUP);     // UP버튼 핀모드 설정
  pinMode(button_down, INPUT_PULLUP);   // DOWN버튼 핀모드 설정
  pinMode(button_ok, INPUT_PULLUP);     // OK버튼 핀모드 설정
  
  lcd.begin(16,2);  // lcd 디스플레이 설정
                   
  lcd.setCursor(0, 0);          // 초기메세지 좌표설정
  lcd.print("Hello World");     // 전원 켤때 초기 메세지 (수정요망)
  delay(1000);                  // 전원 켤때 메세지 표기시간 1s 
  
  lcd.clear();  // lcd setup (화면 초기화)
  page_0();     // PAGE 0(초기화면)으로 이용
}

void loop() {
  switch(page){      
     case 0 : page_0(); break;  // page 값 0이면 페이지 0  - 초기화면부 
     case 1 : page_1(); break;  // page 값 1이면 페이지 1  - 모드선택부
     case 2 : page_2(); break;  // page 값 2이면 페이지 2  - 작동부
   }
}

void page_0(){
  while(digitalRead(button_ok) == HIGH){
    lcd.setCursor(0, 0);                               // LCD 좌표 설정
    lcd.print("Enter the Locker to be used :");        // 내용 그대로
        
    lcd.setCursor(0, 1);                               // LCD 좌표 설정
    lcd.print("Locker : "); lcd.print(count);          // 라커번호 설정 


    if (digitalRead(button_up) == LOW){ count ++; delay(200);}                      // UP버튼 누르면 변수값+1
    if (digitalRead(button_up) == HIGH){}

    if (digitalRead(button_down) == LOW && count != 0){ count --; delay(200);}      // DOWN버튼 누르면 변수값-1
    if (digitalRead(button_down) == HIGH){}  //혹시 어딘가 쓸수 있지 않을까 해서 추가해봄ㅋ 

    if (digitalRead(button_ok) == LOW && count != 0 ){  page_1(); delay(200); }     // OK버튼 누르면 페이지 이동 (락커번호가 0아 아니면)
    if (digitalRead(button_ok) == HIGH){}    //혹시 어딘가 쓸수 있지 않을까 해서 추가해봄ㅋ 
  }  
}

void page_1(){
  delay(500);    // ok버튼 중복입력 방지 delay
     while(1){   // 무한반복
      if(mode%2 == 1){  // 홀수
        lcd.setCursor(0, 0);                         
        lcd.print(">  Perfect mode       ");
        lcd.setCursor(0, 1);  
        lcd.print("   Quick mode            ");
        lcd.display();
        count_time = 9;  // 작동시간 9분 설정 (Perfect mode)
      }
      if(mode%2 == 0){  //짝수
        lcd.setCursor(0, 0);                         
        lcd.print("   Perfect mode        ");
        lcd.setCursor(0, 1);  
        lcd.print(">  Quick mode            ");
        lcd.display();
        count_time = 3;  // 작동시간 3분 설정 (Quick mode)
      }
      
      if (digitalRead(button_up) == LOW){ mode = mode+1; delay(200); }
      if (digitalRead(button_up) == HIGH){}

      if (digitalRead(button_down) == LOW){mode = mode-1; delay(200); }
      if (digitalRead(button_down) == HIGH){}

      if (digitalRead(button_ok) == LOW && count_time != 0){  // OK버튼 눌리면 페이지 이동 (시간이 0이 아니면)
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

      // 락커번호, 작동시간 변수값에 따라 신호전송
      // 하나만 주석 달거임. 
      if(count == 1){
        Serial.print("1번박스 "); Serial.print(count_time); Serial.println(" 분 작동시작");
        if(count_time == 3){
          Wire.write("a");  // 1번 락커 설정
          Wire.write("-");
          Wire.write("g");  // 3분 설정(일종의 암호임)
          Wire.endTransmission();  //설정값 전송시작!
        } if(count_time == 9){
          Wire.write("a");  // 1번 락커
          Wire.write("-");
          Wire.write("i");  // 9분 (일종의 암호임)
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

         // Task finish LCD표기
         lcd.setCursor(0, 0);                         
         lcd.print("Start Work!!           ");
     
         lcd.setCursor(0, 1);   
         lcd.print("[PUSH THE RESET]");
         delay(1000);
         
         if (digitalRead(button_ok) == LOW ){ page = 0; break;  }  //초기화면으로 BACK  // break는 무한반복 탈출
         if (digitalRead(button_ok) == HIGH){}
      }
      
      lcd.clear();  // lcd 화면 초기화
      delay(200);
      page_0();
      page = 0;
}
