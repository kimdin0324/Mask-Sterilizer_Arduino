#include <Wire.h>
#include "Timer.h" 
#include <SimpleTimer.h>  
#define Slave 0x04 // Slave 주소 지정

SimpleTimer timer; 
int num;
int con = 0;
char rec[128]; // Master로부터 온 데이터 저장 할 변수


int box_1 = 2;   
int box_2 = 3;    
int box_3 = 4;   
int box_4 = 5;        
int box_5 = 6;   
int box_6 = 7;  


int box_whether_1 = 0; 
int box_whether_2 = 0;   
int box_whether_3 = 0;  
int box_whether_4 = 0;
int box_whether_5 = 0;    
int box_whether_6 = 0;  

long box_time_1 = 0; 
long box_time_2 = 0;
long box_time_3 = 0;   
long box_time_4 = 0;
long box_time_5 = 0;
long box_time_6 = 0;  

int OR_1 = 0; 
int OR_2 = 0;
int OR_3 = 0;
int OR_4 = 0;
int OR_5 = 0; 
int OR_6 = 0; 

long box_time_save_1 = 0;
long box_time_save_2 = 0;
long box_time_save_3 = 0;
long box_time_save_4 = 0;
long box_time_save_5 = 0;
long box_time_save_6 = 0;
 
Timer t;                            //instantiate the timer object
Timer s;                            //timer for analogRead function.

void setup(void){
  rec[0] = 0; rec[2] = 0;
    Serial.begin(9600);
    Wire.begin(Slave);

    pinMode(box_1, OUTPUT);
    pinMode(box_2, OUTPUT);
    pinMode(box_3, OUTPUT);
    pinMode(box_4, OUTPUT);
    pinMode(box_5, OUTPUT);
    pinMode(box_6, OUTPUT);
    pinMode(13, OUTPUT);

   // t.pulse(box_1, box_time_save_1, box_whether_1); 
    s.every(1000,readData); //1초마다 락커 메모리시간을 감소시시는 함수로 이동
}

void loop( ){
    Wire.onReceive(record);
    t.update(); // if(box_whether_1 == 1) -> 1번 락커 on
    s.update();  // 조건문 씌우지 말것

    if(box_time_save_1 > 0){
      digitalWrite(box_1, HIGH);
    }else if(box_time_save_1 <= 0){
      digitalWrite(box_1, LOW);
      box_whether_1  =  0;
    }


    if(box_time_save_2 > 0){
      digitalWrite(box_2, HIGH);
    }else if(box_time_save_2 <= 0){
      digitalWrite(box_2, LOW);
      box_whether_2  =  0;
    }

    if(box_time_save_3 > 0){
      digitalWrite(box_3, HIGH);
    }else if(box_time_save_3 <= 0){
      digitalWrite(box_3, LOW);
      box_whether_3  =  0;
    }

    if(box_time_save_4 > 0){
      digitalWrite(box_4, HIGH);
    }else if(box_time_save_4 <= 0){
      digitalWrite(box_4, LOW);
      box_whether_4  =  0;
    }

    if(box_time_save_5 > 0){
      digitalWrite(box_5, HIGH);
    }else if(box_time_save_5 <= 0){
      digitalWrite(box_5, LOW);
      box_whether_5  =  0;
    }

    if(box_time_save_6 > 0){
      digitalWrite(box_6, HIGH);
    }else if(box_time_save_6 <= 0){
      digitalWrite(box_6, LOW);
      box_whether_6  =  0;
    }
}

void record(int receiveNum){
   num = receiveNum;
   for(int i = 0; i < receiveNum; i++){ // Master로부터 받은 데이터를 순서대로
     rec[i] = Wire.read(); // rec에 저장
   }
}

void readData(){  
  Serial.println("###################################################");
  Serial.println(rec[0]);
  Serial.println("-");
  Serial.println(rec[2]);
  Serial.println("###################################################");
  
  Serial.println("");
  Serial.println("");
  
  Serial.println("-----------------------------------------------------");  
  Serial.print("1번 락커 :");  Serial.print(box_whether_1); Serial.print(",  "); Serial.print(box_time_save_1); Serial.print(",  "); Serial.print(box_time_1); Serial.println(" 동안 작동시작");
  Serial.println("-----------------------------------------------------");  
  Serial.print("2번 락커 :");  Serial.print(box_whether_2); Serial.print(",  "); Serial.print(box_time_save_2); Serial.print(",  "); Serial.print(box_time_2); Serial.println(" 동안 작동시작");
  Serial.println("-----------------------------------------------------");  
  Serial.print("3번 락커 :");  Serial.print(box_whether_3); Serial.print(",  "); Serial.print(box_time_save_3); Serial.print(",  "); Serial.print(box_time_3); Serial.println(" 동안 작동시작");
  Serial.println("-----------------------------------------------------");   
  Serial.print("4번 락커 :");  Serial.print(box_whether_4); Serial.print(",  "); Serial.print(box_time_save_4); Serial.print(",  "); Serial.print(box_time_4);Serial.println(" 동안 작동시작");
  Serial.println("-----------------------------------------------------");  
  Serial.print("5번 락커 :");  Serial.print(box_whether_5); Serial.print(",  "); Serial.print(box_time_save_5); Serial.print(",  "); Serial.print(box_time_5); Serial.println(" 동안 작동시작");
  Serial.println("-----------------------------------------------------");  
  Serial.print("6번 락커 :");  Serial.print(box_whether_6); Serial.print(",  "); Serial.print(box_time_save_6); Serial.print(",  "); Serial.print(box_time_6); Serial.println(" 동안 작동시작");
  Serial.println("-----------------------------------------------------");  
  
  Serial.println("");
  Serial.println("");


 if(rec[0] == 'a'){ 
        if(rec[2] == 'g'){      Serial.println("1번락커 3분 ON"); box_whether_1 = 1;   box_time_save_1 = 180000; } //3분
        else if(rec[2] == 'i'){ Serial.println("1번락커 9분 ON"); box_whether_1 = 1;   box_time_save_1 = 540000; } //9분
        delay(200);
         rec[0] = 0; rec[2] = 0;
    }  
     if(rec[0] == 'b'){ 
        if(rec[2] == 'g'){      Serial.println("2번락커 3분 ON"); box_whether_2 = 1; box_time_save_2 = 180000;  } //3분
        else if(rec[2] == 'i'){ Serial.println("2번락커 9분 ON"); box_whether_2 = 1; box_time_save_2 = 540000;  } //9분
        delay(200);
        rec[0] = 0; rec[2] = 0;
    }

     if(rec[0] == 'c'){ 
        if(rec[2] == 'g'){       Serial.println("3번락커 3분 ON"); box_whether_3 = 1; box_time_save_3 = 180000;  } //3분
        else if(rec[2] == 'i'){  Serial.println("3번락커 9분 ON"); box_whether_3 = 1; box_time_save_3 = 540000;  } //9분
        delay(200);
        rec[0] = 0; rec[2] = 0;
    }

     if(rec[0] == 'd'){ 
        if(rec[2] == 'g'){       Serial.println("4번락커 3분 ON"); box_whether_4 = 1;  box_time_save_4 = 180000; } //3분
        else if(rec[2] == 'i'){  Serial.println("4번락커 9분 ON"); box_whether_4 = 1;  box_time_save_4 = 540000; } //9분
        delay(200);
        rec[0] = 0; rec[2] = 0;
    }

     if(rec[0] == 'e'){ 
        if(rec[2] == 'g'){       Serial.println("5번락커 3분 ON"); box_whether_5 = 1;  box_time_save_5 = 180000; } //3분
        else if(rec[2] == 'i'){  Serial.println("5번락커 9분 ON"); box_whether_5 = 1;  box_time_save_5 = 540000; } //9분
        delay(200);
        rec[0] = 0; rec[2] = 0;
    }

     if(rec[0] == 'f'){ 
        if(rec[2] == 'g'){       Serial.println("6번락커 3분 ON"); box_whether_6 = 1;  box_time_save_6 = 180000; } //3분
        else if(rec[2] == 'i'){  Serial.println("6번락커 9분 ON"); box_whether_6 = 1;  box_time_save_6 = 540000; } //9분
        delay(200);
        rec[0] = 0; rec[2] = 0;
    }

    
   if(box_time_save_1 != 0){
      box_time_save_1 = box_time_save_1 - 1000;
    }

    if(box_time_save_2  != 0 ){
      box_time_save_2 = box_time_save_2 - 1000;
    }

    if(box_time_save_3  != 0 ){
      box_time_save_3 =  box_time_save_3 - 1000;
    }

    if(box_time_save_4 != 0){
      box_time_save_4 = box_time_save_4 - 1000;
    }

    if(box_time_save_5  != 0 ){
      box_time_save_5 = box_time_save_5 - 1000;
      
    }

    if(box_time_save_6  != 0 ){
      box_time_save_6 = box_time_save_6 - 1000;
      
    }
      /*
   if(box_time_1 <= 0 ){
     box_whether_1  =  0;
     box_time_save_1 = 0;
     
   } if(box_time_2 <= 0){
     box_whether_2  =  0;
     box_time_save_2 = 0;
     
   } if(box_time_3 <= 0){
     box_whether_3  =  0;
     box_time_save_3 = 0;
     
   } if(box_time_4 <= 0){
     box_whether_4  =  0;
     box_time_save_4 = 0;
     
   } if(box_time_5 <= 0){
     box_whether_5  =  0;
     box_time_save_5 = 0;
     
   } if(box_time_6 <= 0){
     box_whether_6  =  0;
     box_time_save_6 = 0;
   }*/

  // rec[0] = 0; rec[2] = 0;
   
}
