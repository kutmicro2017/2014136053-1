
#define Up_R 1 //상 신호등
#define Up_Y 2
#define Up_G 3 
#define Do_R 4 //하 신호등
#define Do_Y 5
#define Do_G 6
#define Le_R 7 // 좌 신호등
#define Le_Y 8
#define Le_G 9
#define Ri_R 10 // 우 신호등
#define Ri_Y 11
#define Ri_G 12 
#define Button_A 13 // 스위치
int interval = 40000; //40초
volatile bool state = true; //스위치 변수, 누를 시 false

void setup() {  // OUTPUT 세팅
  pinMode(Up_R, OUTPUT);
  pinMode(Up_G, OUTPUT);
  pinMode(Up_Y, OUTPUT);
  pinMode(Do_R, OUTPUT);
  pinMode(Do_G, OUTPUT);
  pinMode(Do_Y, OUTPUT);
  pinMode(Le_R, OUTPUT);
  pinMode(Le_G, OUTPUT);
  pinMode(Le_Y, OUTPUT);
  pinMode(Ri_R, OUTPUT);
  pinMode(Ri_G, OUTPUT);
  pinMode(Ri_Y, OUTPUT);
  pinMode(Button_A, INPUT_PULLUP); //기본값 HIGH input과는 다르게 프로세서 내부 저항을 사용
  attachInterrupt(0,Botton, FALLING); //인터럽트0, 0번 핀으로 인터럽트 처리, FALLING은 신호가 high에서 low가 될때 실행시키겠다의 뜻
}                               //즉 인터럽트 핀의 값이 HIGH에서 LOW로 바뀔 때 함수Botton 실행
                                 //인터럽트는 지정된 핀의 현재 상태가 어떻게 변하느냐에 따라 결정되고, 인터럽트가 발생됐다면 loop()안의 코드 실행이 중단되고 인터럽트로 지정된 함수가 실행됨.

void loop() {
// -----------------------------------------------------
//순서는 상-하-좌-우
// -----------------------------------------------------


//------------맨처음, 상 신호등만 초록색 ----------------  
digitalWrite(Le_R, HIGH);
digitalWrite(Ri_R, HIGH);
digitalWrite(Do_R, HIGH);
digitalWrite(Up_R, LOW);
digitalWrite(Up_G, HIGH);
delay(40000); //40초 동안 유지
//------------------------------------------------------
digitalWrite(Up_G, LOW); // 상 신호등 초록색 꺼짐

// -------------초록색 -> 빨간색 될때 ------------------------
Yellow(Up_Y);
// --------------------------------------------------------
// ---------------------하 신호등 빨간불이 초록불로 바뀜------------------------
digitalWrite(Up_R, HIGH); 
digitalWrite(Do_R, LOW);
digitalWrite(Do_G, HIGH); 
// ------------------------------------------------------------------------------

unsigned long currentMillis = millis(); // 현재시각 체크, millis() 함수가 현재시간(아두이노가 시작된 후부터 경과된 시간)을 밀리초 단위로(1/1000 초) 리턴
while(millis() - currentMillis <= interval) { // 앞으로 40초동안 반복
 if(state == false) { //스위치가 눌렸으면
    delay(3000); //3초 대기
    digitalWrite(Do_G, LOW); // 하 신호등 초록불을 꺼준다
    Yellow(Do_Y); // 하 신호등 노란불 점멸
    digitalWrite(Do_R, HIGH); // 하 신호등 빨간불을 켠다
    state = true; // 상태를 처음의 ture 로 바꿔줌
 }
}


if(digitalRead(Do_G) == HIGH) { //스위치가 눌리지 않았을 경우 진행
    digitalWrite(Do_G, LOW);  // 하 초록불 꺼짐
    Yellow(Do_Y); // 하 노란불 점멸
    digitalWrite(Do_R, HIGH); // 하 빨간불 켜짐
}



digitalWrite(Do_R, HIGH);  // 하 빨간불 켜져있음
digitalWrite(Le_R, LOW); // 좌 빨간불 꺼짐
digitalWrite(Le_G, HIGH); // 좌 신호등 초록불만 켜짐
delay(40000); //40초간 유지
digitalWrite(Le_G, LOW); //좌 초록불 꺼짐
Yellow(Le_Y); //좌 노란불 점멸
digitalWrite(Le_R, HIGH); // 좌 빨간불 켜짐


digitalWrite(Ri_R, LOW); // 우 빨간불 꺼짐
digitalWrite(Ri_G, HIGH);  // 우 초록불 켜짐
delay(40000); 
digitalWrite(Ri_G, LOW); // 우 초록불 꺼짐
Yellow(Ri_Y); // 우 노란불 점멸
digitalWrite(Ri_G, LOW); // 우 초록불 꺼짐
digitalWrite(Ri_R, HIGH); // 우 빨간불 켜짐

}











//----------------------------------함수들--------------------------------
void Botton(){ //스위치가 눌렸을 때 실행되는 함수
 if(digitalRead(Do_G) == HIGH) state = false; //스위치가 눌리면 state의 값을 바꿔준다
}




void Yellow(const int LED) {  //yellow신호 점멸
   for(int i =0; i < 10; i++) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
   }
}

//----------------------------------------------------------------------------




