#include <Servo.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

#define TRIG 6
#define ECHO 7

Servo servoMotor;

int getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  return duration * 0.034 / 2;
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  servoMotor.attach(5);
  servoMotor.write(90);

  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();

  if (distance > 20) {
    forward();
  } else {
    stopMotors();
    delay(300);

    backward();
    delay(400);
    stopMotors();

    servoMotor.write(150);
    delay(500);
    int leftDist = getDistance();

    servoMotor.write(30);
    delay(500);
    int rightDist = getDistance();

    servoMotor.write(90);

    if (leftDist > rightDist) {
      left();
    } else {
      right();
    }

    delay(500);
    stopMotors();
  }
}
