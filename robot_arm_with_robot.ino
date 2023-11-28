#include <Servo.h>

#define Echo_1 A0
#define Trig_1 A1
#define Echo_2 A2
#define Trig_2 A3

#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
#define ENA 10
#define ENB 9

Servo servo_1;
Servo servo_2;
Servo servo_3;

void setup() 
{
/*robot arm servos*/
  servo_1.attach(0);
  servo_2.attach(1);
  servo_3.attach(2);

/*Ultrasonic sesors*/
  pinMode(Trig_1, OUTPUT);
  pinMode(Echo_1, INPUT);
  pinMode(Trig_2, OUTPUT);
  pinMode(Echo_2, INPUT);

/*motor wheels*/
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() 
{
/*  int distance_1 = obstacle_1();
  int distance_2 = obstacle_2();*/
  int Flage=0; 


  if (Flage==0)
  { 
    delay(100);
    Forward();
    Flage=1;  
  }

  while(Flage==1)
  {
    int distance_1 = obstacle_1();
    int distance_2 = obstacle_2();
    
    if ((distance_2 <= 9) && (distance_1 > 9))
    {
      delay(100);
      Stop();
      delay(1000);
    //  robotArm_2();
      delay(1000);
      Forward();
    }
   
    if((distance_1 <= 9) && (distance_2 > 9))
    {
      delay(10);
      Stop();
     delay(100);
    /*
    //43-->-90', 93-->0', 142-->+90'
    servo_1.write(142);
    servo_2.write(93);
    servo_3.write(43); 
    */ 
      robotArm_1();
      delay(1000);
      Backward();
    }
  }
}



void Forward()
{
  
  analogWrite(ENA,255);
  analogWrite(ENB,255);

  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
 /* for (int i=0; i<255; i=+5)
    {
      analogWrite(ENA,i); 
      analogWrite(ENB,i); 
      delay(20);
    } 
  */
}

void Backward()
{
  /*
  analogWrite(ENA,255);
  analogWrite(ENB,255);
*/
  for (int i=0; i<256; i=+5)
    {
      analogWrite(ENA,i); 
      analogWrite(ENB,i); 
      delay(20);
    }
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void Stop()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

int obstacle_1() {
  digitalWrite(Trig_1, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_1, LOW);
  long t = pulseIn(Echo_1, HIGH);
  int cm_1 = t / 29 / 2;
  return cm_1;
}

int obstacle_2() {
  digitalWrite(Trig_2, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_2, LOW);
  long t = pulseIn(Echo_2, HIGH);
  int cm_2 = t / 29 / 2;
  return cm_2;
}


void robotArm_1() {
  
  for (int S3value = 93; S3value <= 140; S3value++) {
    servo_3.write(S3value);
    delay(10);
  }
    delay(1000);
  for (int S2value = 93; S2value <= 140; S2value++) {
    servo_2.write(S2value);
    delay(10);
  }
    delay(1000);
  for (int S1value = 93; S1value >= 43; S1value--) {
    servo_1.write(S1value);
    delay(10);
  }

    delay(2000);

  for (int S3value = 140; S3value >= 93; S3value--) {
    servo_3.write(S3value);
    delay(10);
  }
      delay(1000);
  for (int S2value = 140; S2value >= 93; S2value--) {
    servo_2.write(S2value);
    delay(10);
  }
    delay(1000);
  for (int S1value = 43; S1value <= 93; S1value++) {
    servo_1.write(S1value);
    delay(10);
  }
}


void robotArm_2() {
  
  for (int S3value = 0; S3value <= 180; S3value++) {
    servo_3.write(S3value);
    delay(10);
  }

  for (int S2value = 0; S2value <= 180; S2value++) {
    servo_2.write(S2value);
    delay(10);
  }

  for (int S1value = 180; S1value >= 0; S1value--) {
    servo_1.write(S1value);
    delay(10);
  }
}
