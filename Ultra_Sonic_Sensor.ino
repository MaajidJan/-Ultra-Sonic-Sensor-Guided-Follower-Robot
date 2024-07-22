#include <AFMotor.h>

AF_DCMotor Motor1(1);  // Motor connected to M1
AF_DCMotor Motor2(2);  // Motor connected to M2
AF_DCMotor Motor3(3);  // Motor connected to M3
AF_DCMotor Motor4(4);  // Motor connected to M4

int echoLeft = A2;      // Echo Pin for left ultrasonic sensor
int trigLeft = A3;      // Trig Pin for left ultrasonic sensor
int echoFront = A5;     // Echo Pin for right ultrasonic sensor
int trigFront = A4;     // Trig Pin for right ultrasonic sensor

   // Delay in milliseconds before stopping motors (3 seconds in this example)

void setup() {
  Serial.begin(9600);
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);

  // Set initial motor speeds
  Motor1.setSpeed(0);
  Motor2.setSpeed(0);
  Motor3.setSpeed(0);
  Motor4.setSpeed(0);
  Motor1.run(RELEASE);
  Motor2.run(RELEASE);
  Motor3.run(RELEASE);
  Motor4.run(RELEASE);
}

void loop() {
  int leftDistance, rightDistance;

  // Measure distances
  digitalWrite(trigLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigLeft, LOW);
  rightDistance = pulseIn(echoLeft, HIGH) / 58;

  digitalWrite(trigFront, LOW);
  delayMicroseconds(2);
  digitalWrite(trigFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFront, LOW);
  leftDistance = pulseIn(echoFront, HIGH) / 58;

  // Output distances
  Serial.print("Left Distance: ");
  Serial.print(leftDistance);
  Serial.print(" cm, Right Distance: ");
  Serial.print(rightDistance);
  Serial.println(" cm");

  // Adjust speed based on distances
  int speed = 200;
  if (rightDistance > 5 && rightDistance < 25 && leftDistance < 25 && leftDistance > 5) {
    // Obstacle detected in front, go backward
    Motor1.setSpeed(speed);
    Motor2.setSpeed(speed);
    Motor3.setSpeed(speed);
    Motor4.setSpeed(speed);
    Motor1.run(FORWARD);
    Motor2.run(FORWARD);
    Motor3.run(FORWARD);
    Motor4.run(FORWARD);
  } else if (leftDistance < 15 && leftDistance > 4) {
    // Obstacle detected on the left, turn right
    Motor1.setSpeed(speed);
    Motor2.setSpeed(speed);
    Motor3.setSpeed(speed );
    Motor4.setSpeed(speed );
    Motor1.run(FORWARD);
    Motor2.run(FORWARD);
    Motor3.run(BACKWARD);
    Motor4.run(BACKWARD);
  } else if (rightDistance > 4 && rightDistance < 15) {
    // Obstacle detected on the right, turn left
    Motor1.setSpeed(speed );
    Motor2.setSpeed(speed );
    Motor3.setSpeed(speed );
    Motor4.setSpeed(speed );
    Motor1.run(BACKWARD);
    Motor2.run(BACKWARD);
    Motor3.run(FORWARD);
    Motor4.run(FORWARD);
  } else if (leftDistance >= 2 && rightDistance <=4) {
    // Between 4 and 5 cm, go backward
    Motor1.setSpeed(speed);
    Motor2.setSpeed(speed);
    Motor3.setSpeed(speed);
    Motor4.setSpeed(speed);
    Motor1.run(BACKWARD);
    Motor2.run(BACKWARD);
    Motor3.run(BACKWARD);
    Motor4.run(BACKWARD);
  } else {
    
      Motor1.setSpeed(0);
      Motor2.setSpeed(0);
      Motor3.setSpeed(0);
      Motor4.setSpeed(0);
      Motor1.run(RELEASE);
      Motor2.run(RELEASE);
      Motor3.run(RELEASE);
      Motor4.run(RELEASE);
    
  }


  delay(100); // Delay for stability
}
