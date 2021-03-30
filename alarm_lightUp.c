#include <Adafruit_NeoPixel.h>

#include <stdio.h>
#include <stdlib.h>

int numOfLed = 20;	// led 수
int led_pin1 = 10;	
int led_pin2 = 12;	
int led_pin3 = 11;	
int btn_pin = A0;	
int btn =4;
int state = 0;		// 상태 확인, 0이면 사용 가능, 1이면 사용 중
int data = 0;		// 시간값

// 알람용
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numOfLed, led_pin1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(numOfLed, led_pin2, NEO_GRB + NEO_KHZ800);
// 사용 중 표시용
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(numOfLed, led_pin3, NEO_GRB + NEO_KHZ800);

void setup (){
  Serial.begin(9600);
  pinMode(btn, INPUT);
}
 
void loop(){
  // 버튼 입력 시 state를 1로 변경
  int value = digitalRead(btn);
  if(value == 0)
  {
    if(state == 0)
    {
      state=1;
      delay(100);
    }
  }
  
  // state가 0이면 가변장치의 값을 읽음, 0~102
  if(state == 0)
  {
    lightUp_green();
    data = analogRead(btn_pin)/10;
    Serial.println(data);
  }
  // state가 1일 때, 타이머 시작
  else if (state == 1)
  {
    if(data > 0){
      lightUp_red();
      Serial.println(data);
      delay(1000);
      data = data - 1;
    }
    // 타이머 마치면 led 점등
    else
    {
      lightUp_green();
      lightUp_slowly();
    }
  }
}

// 알람용 led 천천히 점등
void lightUp_slowly(){
  Serial.println("Light up");
  for(int i=0; i<256; i++){
    for(int j=0; j<strip.numPixels(); j++){
        strip.setPixelColor(j,strip.Color(i,i,0));  
      	strip2.setPixelColor(j,strip.Color(i,i,0));  
      }
    strip.show();
    strip2.show();
    delay(2);
  }
}

// 사용 확인 led 녹색불 점등
void lightUp_green(){
  for(int i = 0; i < strip3.numPixels(); i++){
    strip3.setPixelColor(i, strip3.Color(0,255,0));
  }
  strip3.show();
}

// 사용 확인 led 적색불 점등
void lightUp_red(){
  for(int i = 0; i < strip3.numPixels(); i++){
    strip3.setPixelColor(i, strip3.Color(255,0,0));
  }
  strip3.show();
}