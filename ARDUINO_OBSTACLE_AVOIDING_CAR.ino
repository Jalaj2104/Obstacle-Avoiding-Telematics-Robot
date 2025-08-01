// OBSTACLE AVOIDING ROBOT + MQ-135 AIR QUALITY SENSOR
// Required Libraries:
// - AFMotor: https://learn.adafruit.com/adafruit-motor-shield/library-install
// - NewPing: https://github.com/livetronic/Arduino-NewPing
// - Servo: Built-in or https://github.com/arduino-libraries/Servo

#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

// Define ultrasonic sensor pins
#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200

// Define MQ-135 sensor pin
#define MQ135_PIN A2

// Motor setup
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

// Ultrasonic + Servo
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;

// Robot status
boolean goesForward = false;
int distance = 100;
int speedSet = 0;
#define MAX_SPEED 190

void setup() {
  Serial.begin(9600);
  myservo.attach(10);
  myservo.write(115);
  delay(2000);

  // Initial ping
  distance = readPing();
  delay(100);
}

void loop() {
  // --- Air Quality Monitoring ---
  int gasValue = analogRead(MQ135_PIN);
  float ppm = map(gasValue, 0, 1023, 0, 1000);
  Serial.print("Air Quality: ");
  Serial.print(ppm);
  Serial.print(" ppm - ");
  if (ppm > 700) {
    Serial.println("Poor");
  } else if (ppm > 300) {
    Serial.println("Moderate");
  } else {
    Serial.println("Good");
  }

  // --- Obstacle Avoidance ---
  int distanceR = 0;
  int distanceL = 0;
  delay(40);

  if (distance <= 15) {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }

  distance = readPing();
}

// --- Look Right ---
int lookRight() {
  myservo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}

// --- Look Left ---
int lookLeft() {
  myservo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}

// --- Read Ultrasonic Distance ---
int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

// --- Motor Controls ---
void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
