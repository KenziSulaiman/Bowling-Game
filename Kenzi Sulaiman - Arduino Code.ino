#include <Servo.h>

Servo myservo;
const int pingPin = 7;
const int buttonPin = 2;   // Pin connected to the button switch
const int ledPin = 3;      // Pin connected to the LED
const int buzzerPin = 4;   // Pin connected to the buzzer
const int trigPin = A0;
const int echoPin = A1;

bool ballEntered = false;

bool repeat = true;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Internal pull-up resistor
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  myservo.attach(9);  // Servo connected to PWM pin 9
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  float distance = measureDistance(trigPin, echoPin);
  Serial.println(distance);
  
  if (distance < 20 && distance >5 && repeat == true) {  // If the object is closer than 5cm
    ballEntered = true;
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    playBuzzer();
    throwBall();  // Move the servo to simulate throwing the ball
    Serial.println("Ball thrown!");
    repeat = false;
  } else {
    ballEntered = false;
    digitalWrite(ledPin, LOW);  // Turn off the LED
    stopServo();  // Stop the servo
    repeat = true;
  }
  
}

void playBuzzer() {
  tone(buzzerPin, 1000, 200);  // Play a sound for 200 milliseconds
  delay(300);                  // Pause for 300 milliseconds
  noTone(buzzerPin);           // Turn off the buzzer
}

float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float cm = duration*0.034/2;
  return cm;
}

void throwBall() {
  myservo.write(45);  // Adjust the servo position as needed
  delay(500);  // Adjust the delay based on the servo speed
  myservo.write(0);
  delay(500);
}

void stopServo() {
  myservo.write(45);  // Stop the servo at a neutral position
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}
