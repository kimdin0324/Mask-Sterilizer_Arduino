# Mask-Sterilizer_Arduino
신흥고 세특용 아두이노 마스크 살균기입니다.

## 제작동기
코로나19로 인해 마스크의 수요량이 증가하였습니다.   
그로 인해 마스크의 가격이 폭등하였고, 마스크를 빨아서 2번 이상 쓰는 일도 있다는걸 알게 되었습니다  
한 마스크를 계속 쓰게 되면 마스크를 써도 코로나를 효과적으로 막아낼 수 없는데도 말이죠...  
또한 하루 종일 마스크를 사용하다보면 마스크 안에 침과 여러 세균들이 많이 생기게 됩니다   
이러한 문제점들을 직접 마주하며 마스크 살균장치를 만들게 되었습니다!!  
~~나쁜 코로나 쉑~~

## 기능명세
> 하드웨어적 요소
>	> **아두이노 보드**  
> > 제어보드로는 메가와 우노를 함께 사용했습니다  
> > 컨트롤 박스를 크게 만들어도 되는 조건이었기에 굳이 나노를 사용하지 않았습니다!  
> > 아두이노에서 입력를 받으면서도 출력을 하는 객체적 작업을 가능하게 했습니다. (Timer, I2C)   

> > > I2C 통신  
> > > I2C는 두 개의 신호(SDA, SCL)로 다수의 디바이스와 데이터를 송/수신할 수 있는 통신방식입니다. 
      하나의 마스터와 다수의 슬레이브로 구성되며, 마스터에서 기준클럭(SCL)을 생성하고, 이 클럭에 맞춰 데이터(SDA)를 전송 및 수신합니다. 
      각 송신과 수신은 구분되어 있는 반이중 방식입니다. 각 슬레이브는 개별 주소(어드레스)를 가지고 있으며, 이 주소를 통해 식별이 가능합니다. 
      즉, 기준클럭과 데이터는 I2C 네트워크의 모든 디바이스에게 전달되고, 해당 주소를 가진 디바이스만 응답하는 방식으로 서로 데이터를 주고 받습니다.   

> > > 아두이노 Multi-tasking (used Timer)  
> > > 아두이노 는 단순하고 파워풀한 프로세서입니다. 
      운영체제가 없고 한번에 하나의 일만 처리합니다. 보통 시간의 지연이 필요한 기능은 delay() 함수를 사용해 프로그램을 잠시 멈추는 방법을 사용합니다. 
      그러나 delay()를 사용하는 것은 프로세서를 단일한 방향으로만 동작하게 하는 것이라고 할 수 있습니가 즉, 바쁘니까 기다리라고 하는 것입니다. 
      프로세서가 100% 몰려있으니 delay 가 수행되는 동안에는 어떤 입력도 받을 수 없고, 출력도 할 수 없죠.  
      그래서 저는 Timer 라이브러리의 기능을 활용해 아두이노 내에 두 클래스를 생성하고 변수를 선언해 멀티 태스킹을 구현했습니다.   
  
> > **UV LED**   
> > UV LED는 스팩트럼에 따라 많은 방법으로 분류됩니다.   
    이 중 태양광에 대한 ISO 분류 기준 ISO-DIS-21348에 따른 분류법을 소개하면 
    UVA(400~315nm), UVB(315~280nm), UVC(280~100nm)로 나눌 수 있습니다.  
    제가 사용한 것은 이중 살균효과가 가장 뛰어난 UV-C타입으로 315-400nm의 파장을 지니며  
    살균, 오존 탐지, 표면이나 물 오염 제거, 단백질 분석, DNA스쿼엔싱, 약 개발 등에 이용됩니다.  
        
> 소프트웨어적 요소  
> > **우노 - 메가 통신 (알파벳 별 락커번호 및 작동시간)**  
> > > a - 1번 락커     
      b - 2번 락커    
      c - 3번 락커     
      d - 4번 락커     
      e - 5번 락커    
      f - 6번 락커      
> > > g - 작동시간 3분    
      h - 작동시간 6분     
      i - 작동시간 9분   
      j - 작동시간 12분   
      k - 작동시간 15분   
        
> > **LCD 페이지**  
> > > page 0 : 초기화면부  
> > > page 1 : 모드선택부  
> > > page 2 : 작동부  

> > **함수설명**  
> > > UNO CODE
> > > > setup & loop  
> > > > setup : 초기설정  
        loop : 반복부 (페이지 변수에 따른 페이지 설정만 담당)  
        
> > > > page_0 & page_1 & page_2  
> > > > LCD 디스플레이에 표시될 내용 출력부  
> > > > (위에 LCD 페이지 참고하셈)  

> > > MEGA CODE  
> > > > setup & loop
> > > > setup : 초기설정, 1초마다 메모리시간을 감소시시는 함수로 이동  
        loop : 함수 업데이트, 락커 ON/OFF  
        record : 메가로부터 I2C통신을 통해 받은 신호를 저장하는 함수   
        readData : 신호 전달값 확인, 작동 테스트, 알파벳으로 전달된 락커번호와 작동시간 해석 및 저장   
        (위에 알파벳 별 뜻 참고하셈)  
   

      

