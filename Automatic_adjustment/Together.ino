#define Joy_UD A0 //x
#define Joy_LR A1 //y

#include <Servo.h>

Servo left_UD_servo;
Servo left_LR_servo;

Servo back_UD_servo;
Servo back_LR_servo;

Servo right_UD_servo;
Servo right_LR_servo;

// 모터들의 위치를 기억하기 위한 변수
unsigned char left_LR_servo_fix=90;
unsigned char left_UD_servo_fix=90;

unsigned char back_LR_servo_fix=90;
unsigned char back_UD_servo_fix=90;

unsigned char right_LR_servo_fix= 90;
unsigned char right_UD_servo_fix=90;

void setup() {
  Serial.begin(9600); // set the baud rate
  
  left_UD_servo.attach(2);
  left_LR_servo.attach(3);
  back_UD_servo.attach(4);
  back_LR_servo.attach(5);
  right_UD_servo.attach(6);
  right_LR_servo.attach(7);

  left_LR_servo.write(left_LR_servo_fix);
  left_UD_servo.write(left_UD_servo_fix);  
  right_LR_servo.write(right_LR_servo_fix);
  right_UD_servo.write(right_UD_servo_fix);
  back_LR_servo.write(back_LR_servo_fix);
  back_UD_servo.write(back_UD_servo_fix);
  delay(1000);

// joystick 모터 수동 제어
  pinMode(24,INPUT);
  pinMode(26,INPUT);
  pinMode(28,INPUT);
  
  pinMode(25,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(29,OUTPUT);
  digitalWrite(25,LOW);
  digitalWrite(27,LOW);
  digitalWrite(29,LOW);

// 릴레이 스크린 라이트 제어
  pinMode(50,INPUT);
  pinMode(51,OUTPUT);
  pinMode(52,OUTPUT);
  digitalWrite(51,HIGH);
  digitalWrite(52,HIGH);
}

// control 전역변수는 굳이 없어도되지만 헷갈려서 선언함.
// control은 라즈베리파이의 비디오 얼굴 인식으로 값을 받아 모든 거울의 모든 모터를 회전시키는 용도
bool video_control=0;

// video_Auto 함수에서 좌우모터 회전인지 상하모터 회전인지 설정
bool servo_LR=0;
bool servo_UD=0;

bool onoff=0;
bool select_mirror=0;  // 거울이 선택되지 않으면 모터 회전 명령을 무시하도록 하기 위함.
bool right_mirror=0;
bool left_mirror=0;
bool back_mirror=0;

bool servo_left_turn=0;
bool servo_right_turn=0;
bool servo_up_turn=0;
bool servo_down_turn=0;

short d = 0;

// while문 내부에서 serial로 받을 숫자를 각도로 인식하기 위한 위한 변수 선언
unsigned char f=0;

char stack=0;

char Button_power1=LOW;
char Button_power2=LOW;
char Button_power3=LOW;

char screen_power=LOW;

bool left_mirror_button=0;
bool back_mirror_button=0;
bool right_mirror_button=0;

bool select_mirror_button=0;

void loop() {
// 버튼/조이스틱으로 거울 수동 조작
  char value1=digitalRead(24);
  char value2=digitalRead(26);
  char value3=digitalRead(28);
  
  if(value1==HIGH && Button_power1==LOW){
    if(Button_power2==HIGH || Button_power3==HIGH){
      Button_power1=HIGH;
      Button_power2=LOW;
      Button_power3=LOW;
      left_mirror_button=1;
      back_mirror_button=0;
      right_mirror_button=0;
      select_mirror_button=1;
      digitalWrite(25,HIGH);
      digitalWrite(27,LOW);
      digitalWrite(29,LOW);
      delay(1000);
    }else{
      Button_power1=HIGH;
      left_mirror_button=1;
      back_mirror_button=0;
      right_mirror_button=0;
      select_mirror_button=1;
      digitalWrite(25,HIGH);
      delay(1000);
    }    
  }else if(value1==HIGH && Button_power1==HIGH){
    Button_power1=LOW;
    left_mirror_button=0;
    back_mirror_button=0;
    right_mirror_button=0;
    select_mirror_button=0;
    digitalWrite(25,LOW);
    delay(1000);
  }
  
  if(value2==HIGH && Button_power2==LOW){
    if(Button_power1==HIGH || Button_power3==HIGH){
      Button_power2=HIGH;
      Button_power1=LOW;
      Button_power3=LOW;
      back_mirror_button=1;
      left_mirror_button=0;
      right_mirror_button=0;
      select_mirror_button=1;
      digitalWrite(27,HIGH);
      digitalWrite(25,LOW);
      digitalWrite(29,LOW);
      delay(1000);
    }else{
      Button_power2=HIGH;
      back_mirror_button=1;
      left_mirror_button=0;
      right_mirror_button=0;
      select_mirror_button=1;
      digitalWrite(27,HIGH);
      delay(1000);
    }
  }else if(value2==HIGH && Button_power2==HIGH){
    Button_power2=LOW;
    back_mirror_button=0;
    left_mirror_button=0;
    right_mirror_button=0;
    select_mirror_button=0;
    digitalWrite(27,LOW);
    delay(1000); 
  }
  
  if(value3==HIGH && Button_power3==LOW){
    if(Button_power1==HIGH || Button_power2==HIGH){
      Button_power3=HIGH;
      Button_power1=LOW;
      Button_power2=LOW;
      right_mirror_button=1;
      left_mirror_button=0;
      back_mirror_button=0;
      select_mirror_button=1;
      digitalWrite(29,HIGH);
      digitalWrite(25,LOW);
      digitalWrite(27,LOW);
      delay(1000);
    }else{
      Button_power3=HIGH;
      right_mirror_button=1;
      left_mirror_button=0;
      back_mirror_button=0;
      select_mirror_button=1;
      digitalWrite(29,HIGH);
      delay(1000);
    }
  }else if(value3==HIGH && Button_power3==HIGH){
    Button_power3=LOW;
    right_mirror_button=0;
    left_mirror_button=0;
    back_mirror_button=0;
    select_mirror_button=0;
    digitalWrite(29,LOW);
    delay(1000);
  }

  if(select_mirror_button==1){
    short Joy_x=analogRead(Joy_UD);
    short Joy_y=analogRead(Joy_LR);
    if(Joy_x>800){
      if (left_mirror_button==1) turn_up_joy();
      else if (back_mirror_button==1) turn_up_joy();
      else if (right_mirror_button==1) turn_down_joy();
    }else if(Joy_x<200){
      if (left_mirror_button==1) turn_down_joy();
      else if (back_mirror_button==1) turn_down_joy();
      else if (right_mirror_button==1) turn_up_joy();
    }
    
    if(Joy_y>800){
      if (left_mirror_button==1) turn_left_joy();
      else if (back_mirror_button==1) turn_right_joy();
      else if (right_mirror_button==1) turn_right_joy();
    }else if(Joy_y<200){
      if (left_mirror_button==1) turn_right_joy();
      else if (back_mirror_button==1) turn_left_joy();
      else if (right_mirror_button==1) turn_left_joy();
    }
  }
  /*
  Serial.print("L_LR - ");
  Serial.print(left_LR_servo_fix);
  Serial.print(" L_UD - ");
  Serial.print(left_UD_servo_fix);
  Serial.print(" B_LR - ");
  Serial.print(back_LR_servo_fix);
  Serial.print(" B_UD - ");
  Serial.print(back_UD_servo_fix);
  Serial.print(" R_LR - ");
  Serial.print(right_LR_servo_fix);
  Serial.print(" R_UD - ");
  Serial.print(right_UD_servo_fix);
  Serial.println("");
*/
// 스크린 제어
/*  char value4=digitalRead(50);

  if(value4==HIGH && screen_power==LOW){
    screen_power=HIGH;
    digitalWrite(51,LOW);
    digitalWrite(52,LOW);
    delay(1000);
  }else if(value4==HIGH && screen_power==HIGH){
    screen_power=LOW;
    digitalWrite(51,HIGH);
    digitalWrite(52,HIGH);
    delay(1000);
  }
*/  
// ---------------- 아두이노↔라즈베리 통신부 
  if(Serial.available()){ // only send data back if data has been sent
    d = Serial.read(); // read the incoming data
  }

    if (d==141){
      digitalWrite(51,LOW);
      digitalWrite(52,LOW);
      delay(1000);
    }else if(d==142){
      digitalWrite(51,HIGH);
      digitalWrite(52,HIGH);
      delay(1000);
    }

// --------------------------------- 음성인식으로 값을 받아 어떤 거울을 회전시킬지 선택

    if (d==162){
      right_mirror=1;
      select_mirror=1;
      left_mirror=0;
      back_mirror=0;
    }else if(d==161){
      left_mirror=1;
      select_mirror=1;
      right_mirror=0;
      back_mirror=0;
    }else if(d==160){
      back_mirror=1;
      select_mirror=1;
      left_mirror=0;
      right_mirror=0;
    }else if(d==150){
      onoff=1;
    }

// -------------------------------- 이 아래로 거울을 좌우로 돌릴지 상하로 돌릴지 결정 ##여기서 한번 구조를 다시 상기하고 맨 밑으로 내려갈 것##

    if (d==178 && select_mirror==1){
      servo_left_turn=1;
    }else if(d==179 && select_mirror==1){
      servo_right_turn=1;
    }else if(d==176 && select_mirror==1){
      servo_up_turn=1;
    }else if(d==177 && select_mirror==1){
      servo_down_turn=1;
    }else if(d==183){
      servo_left_turn=0, servo_right_turn=0, servo_up_turn=0, servo_down_turn=0;
      right_mirror=0, left_mirror=0, back_mirror=0;
      select_mirror=0;
    }

// -------------------------------이 아래로 결정된 전역변수에 따라 거울을 회전시키는 함수를 호출

    while (onoff==1){
        while(1){
     while (1) {
      if(Serial.available()){
        f=Serial.read();
        if (f==162){
          right_mirror=1;
        }else if(f==161){
          left_mirror=1;
        }else if(f==160){
          back_mirror=1;
        }
        
        if(f==151){
          servo_LR=1;
          break;
        }else if(f==152){
          servo_UD=1;
          break;
        }
        f=0;
      }
     }
     while (1) {
        if(Serial.available()){
        f=Serial.read();
        if (left_mirror==1 && servo_LR==1){
          left_LR_servo.write(f);
          left_LR_servo_fix=f;
          left_mirror=0, servo_LR=0;
          stack+=1;
          break;
        }else if (left_mirror==1 && servo_UD==1){
          left_UD_servo.write(f);
          left_UD_servo_fix=f;
          left_mirror=0, servo_UD=0;
          stack+=1;
          break;
        }else if (back_mirror==1 && servo_LR==1){
          back_LR_servo.write(f);
          back_LR_servo_fix=f;
          back_mirror=0, servo_LR=0;
          stack+=1;
          break;
        }else if (back_mirror==1 && servo_UD==1){
          back_UD_servo.write(f);
          back_UD_servo_fix=f;
          back_mirror=0, servo_UD=0;
          stack+=1;
          break;
        }else if (right_mirror==1 && servo_LR==1){
          right_LR_servo.write(f);
          right_LR_servo_fix=f;
          right_mirror=0, servo_LR=0;
          stack+=1;
          break;
        }else if (right_mirror==1 && servo_UD==1){
          right_UD_servo.write(f);
          right_UD_servo_fix=f;
          right_mirror=0, servo_UD=0;
          stack+=1;
          break;
        }
       }
       f=0;
      }
      if (stack==6){
        delay(1000);
        onoff=0;
        digitalWrite(51,LOW);
        digitalWrite(52,LOW);
        delay(3000);
        digitalWrite(51,HIGH);
        digitalWrite(52,HIGH);
        stack=0;
        break;
      }
        }
    }
//     ## 이 밑을 손대면 될 듯하다.##
    if(servo_left_turn==1){
      if(left_mirror==1) turn_left();
      else if(back_mirror==1) turn_left();
      else if(right_mirror==1) turn_left();
    }else if(servo_right_turn==1){
      if(left_mirror==1) turn_right();
      else if(back_mirror==1) turn_right();
      else if(right_mirror==1) turn_right();
    }else if(servo_up_turn==1){
      if(left_mirror==1) turn_up();
      else if(back_mirror==1) turn_up();
      else if(right_mirror==1) turn_up();
    }else if(servo_down_turn==1){
      if(left_mirror==1) turn_down();
      else if(back_mirror==1) turn_down();
      else if(right_mirror==1) turn_down();
    }

    d=0;
}
