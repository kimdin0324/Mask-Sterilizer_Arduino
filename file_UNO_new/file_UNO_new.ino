#include <Wire.h>         // 메가-우노 간 I2C 통신을 위한 라이브러리
#include "Timer.h"        // 작동 시간측정 & 아두이노 객체지향적 작동을 위한 라이브러리
#define Slave 0x04        // Slave 주소 지정(0x04)

int data_num;       // 메가로부터의 입력신호 크기 저장을 위한 변수
char rec[128];      // Master(메가)로부터 온 데이터 저장 할 변수

int box_1 = 2;  int box_whether_1 = 0;    // 살균락커의 핀번호 변수 (box_number) 
int box_2 = 3;  int box_whether_2 = 0;    // 살균락커의 작동여부 변수 (box_whether_number)
int box_3 = 4;  int box_whether_3 = 0;   
int box_4 = 5;  int box_whether_4 = 0;  
int box_5 = 6;  int box_whether_5 = 0; 
int box_6 = 7;  int box_whether_6 = 0; 

long box_time_save_1 = 0;  // UV락커의 작동지속 시간저장 변수
long box_time_save_2 = 0;
long box_time_save_3 = 0;
long box_time_save_4 = 0;
long box_time_save_5 = 0;
long box_time_save_6 = 0;


// 테스트용 작동여부 변수 (OR_number)
Timer t;                            // UV LED 작동
Timer s;                            // 신호 함수 입력&저장

void setup(void){
   rec[0] = 0; // 입력되는 신호 초기화 (락커번호)
   rec[2] = 0; // 입력되는 신호 초기화 (지속시간)
   
   Serial.begin(9600);
   Wire.begin(Slave);

   pinMode(box_1, OUTPUT);    // 락커 핀번호 정의
   pinMode(box_2, OUTPUT);
   pinMode(box_3, OUTPUT);
   pinMode(box_4, OUTPUT);
   pinMode(box_5, OUTPUT);
   pinMode(box_6, OUTPUT);

   s.every(1000,readData);    //1초마다 락커 메모리시간을 감소시시는 함수로 이동
}

void loop( ){
    Wire.onReceive(record);  // 신호입력 받기
    t.update();  // UV LED ON/OFF 업데이트
    s.update();  // 메모리시간을 감소함수 업데이트

    // if - 락커 시간(box_time_save)이 존재하면, 해당 락커 ON! 
    // else - 락커 시간(box_time_save)이 0 이하면, 해당 락커 OFF!
    if(box_time_save_1 > 0){  digitalWrite(box_1, HIGH);   }
    else if(box_time_save_1 <= 0){  digitalWrite(box_1, LOW); box_whether_1  =  0;   }

    if(box_time_save_2 > 0){  digitalWrite(box_2, HIGH);   }
    else if(box_time_save_2 <= 0){   digitalWrite(box_2, LOW); box_whether_2  =  0;  }

    if(box_time_save_3 > 0){   digitalWrite(box_3, HIGH);  }
    else if(box_time_save_3 <= 0){   digitalWrite(box_3, LOW); box_whether_3  =  0;  }

    if(box_time_save_4 > 0){   digitalWrite(box_4, HIGH);  }
    else if(box_time_save_4 <= 0){   digitalWrite(box_4, LOW); box_whether_4  =  0;  }

    if(box_time_save_5 > 0){   digitalWrite(box_5, HIGH);  }
    else if(box_time_save_5 <= 0){   digitalWrite(box_5, LOW); box_whether_5  =  0;  }

    if(box_time_save_6 > 0){   digitalWrite(box_6, HIGH);  }
    else if(box_time_save_6 <= 0){   digitalWrite(box_6, LOW); box_whether_6  =  0;  }
}

void record(int receiveNum){   //메가로부터 I2C통신을 통해 받은 신호를 저장하는 함수 
   data_num = receiveNum;
   for(int i = 0; i < receiveNum; i++){  // 데이터 크기 활용을 위한 저장
     rec[i] = Wire.read();               // rec배열에 저장
   }
}

void readData(){  
  // 신호 전달값 확인
  // 락커 작동 테스트
/* Serial.println("###################################################");
   Serial.println(rec[0]);
   Serial.println("-");
   Serial.println(rec[2]);
   Serial.println("###################################################");
  
   Serial.println("");
   Serial.println("");
  
   Serial.println("-----------------------------------------------------");  
   Serial.print("1번 락커 :");  Serial.print(box_whether_1); Serial.print(",  "); Serial.print(box_time_save_1); Serial.print(",  ");  Serial.println(" 동안 작동시작");
   Serial.println("-----------------------------------------------------");  
   Serial.print("2번 락커 :");  Serial.print(box_whether_2); Serial.print(",  "); Serial.print(box_time_save_2); Serial.print(",  "); Serial.println(" 동안 작동시작");
   Serial.println("-----------------------------------------------------");  
   Serial.print("3번 락커 :");  Serial.print(box_whether_3); Serial.print(",  "); Serial.print(box_time_save_3); Serial.print(",  "); Serial.println(" 동안 작동시작");
   Serial.println("-----------------------------------------------------");   
   Serial.print("4번 락커 :");  Serial.print(box_whether_4); Serial.print(",  "); Serial.print(box_time_save_4); Serial.print(",  "); Serial.println(" 동안 작동시작");
   Serial.println("-----------------------------------------------------");  
   Serial.print("5번 락커 :");  Serial.print(box_whether_5); Serial.print(",  "); Serial.print(box_time_save_5); Serial.print(",  "); Serial.println(" 동안 작동시작");
   Serial.println("-----------------------------------------------------");  
   Serial.print("6번 락커 :");  Serial.print(box_whether_6); Serial.print(",  "); Serial.print(box_time_save_6); Serial.print(",  "); Serial.println(" 동안 작동시작");
   Serial.println("-----------------------------------------------------");  
  
   Serial.println("");
   Serial.println(""); */
 

    // 메가로부터 온 신호 해석부
    // 알파벳으로 전달된 락커번호와 작동시간 해석 및 저장 
    // 깃허브 Readme 참고
    if(rec[0] == 'a'){ 
        if(rec[2] == 'g'){      Serial.println("1번락커 3분 ON"); box_whether_1 = 1;   box_time_save_1 = 180000; } //3분
        else if(rec[2] == 'i'){ Serial.println("1번락커 9분 ON"); box_whether_1 = 1;   box_time_save_1 = 540000; } //9분
        delay(200);
        rec[0] = 0; rec[2] = 0;
        
    } if(rec[0] == 'b'){ 
        if(rec[2] == 'g'){      Serial.println("2번락커 3분 ON"); box_whether_2 = 1; box_time_save_2 = 180000;  } //3분
        else if(rec[2] == 'i'){ Serial.println("2번락커 9분 ON"); box_whether_2 = 1; box_time_save_2 = 540000;  } //9분
        delay(200);
        rec[0] = 0; rec[2] = 0;
        
    } if(rec[0] == 'c'){ 
        if(rec[2] == 'g'){       Serial.println("3번락커 3분 ON"); box_whether_3 = 1; box_time_save_3 = 180000;  } //3분
        else if(rec[2] == 'i'){  Serial.println("3번락커 9분 ON"); box_whether_3 = 1; box_time_save_3 = 540000;  } //9분
        delay(200);
        rec[0] = 0; rec[2] = 0;
        
    } if(rec[0] == 'd'){ 
        if(rec[2] == 'g'){       Serial.println("4번락커 3분 ON"); box_whether_4 = 1;  box_time_save_4 = 180000; } //3분
        else if(rec[2] == 'i'){  Serial.println("4번락커 9분 ON"); box_whether_4 = 1;  box_time_save_4 = 540000; } //9분
        delay(200);
        rec[0] = 0; rec[2] = 0;
        
    } if(rec[0] == 'e'){ 
        if(rec[2] == 'g'){       Serial.println("5번락커 3분 ON"); box_whether_5 = 1;  box_time_save_5 = 180000; } //3분
        else if(rec[2] == 'i'){  Serial.println("5번락커 9분 ON"); box_whether_5 = 1;  box_time_save_5 = 540000; } //9분
        delay(200);
        rec[0] = 0; rec[2] = 0;
        
    } if(rec[0] == 'f'){ 
        if(rec[2] == 'g'){       Serial.println("6번락커 3분 ON"); box_whether_6 = 1;  box_time_save_6 = 180000; } //3분
        else if(rec[2] == 'i'){  Serial.println("6번락커 9분 ON"); box_whether_6 = 1;  box_time_save_6 = 540000; } //9분
        delay(200);
        rec[0] = 0; rec[2] = 0;
        
    }



    // 락커작동 시간감소부
    // 잔여시간이 0이 아니면 감소 
    if(box_time_save_1 != 0){
      box_time_save_1 = box_time_save_1 - 1000;
      
    } if(box_time_save_2  != 0 ){
      box_time_save_2 = box_time_save_2 - 1000;
      
    } if(box_time_save_3  != 0 ){
      box_time_save_3 =  box_time_save_3 - 1000;
      
    } if(box_time_save_4 != 0){
      box_time_save_4 = box_time_save_4 - 1000;
      
    } if(box_time_save_5  != 0 ){
      box_time_save_5 = box_time_save_5 - 1000;
      
      
    } if(box_time_save_6  != 0 ){
      box_time_save_6 = box_time_save_6 - 1000;
      
    }
}
