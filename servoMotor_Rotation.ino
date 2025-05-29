#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(D6); // Attach the servo to pin D1 of NodeMCU
}

void loop() {
  // Rotate the servo to 0 degrees
  rotateTo(0);
  delay(1000); // Wait for the servo to reach the position
  
  // Rotate the servo to 90 degrees
  rotateTo(90);
  delay(1000); // Wait for the servo to reach the position
  
  // Rotate the servo to 180 degrees
  rotateTo(180);
  delay(1000); // Wait for the servo to reach the position
}

void rotateTo(int angle) {
  // Map the angle value (0 to 180) to the servo's range (0 to 180)
  int servoAngle = map(angle, 0, 180, 0, 180);
  
  // Set the servo to the specified angle
  servo.write(servoAngle);
}