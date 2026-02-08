#include <Arduino.h>
#include "Config.h"

// Line Sensors
const int irLineLeft = 4;
const int irLineRight = 2;

void setup()
{
  pinMode(motorRF, OUTPUT);
  pinMode(motorRB, OUTPUT);
  pinMode(motorLF, OUTPUT);
  pinMode(motorLB, OUTPUT);

  pinMode(irLineLeft, INPUT);
  pinMode(irLineRight, INPUT);
}

// --- Smooth Direction Functions using PWM ---

void moveForward()
{
  analogWrite(motorRF, moveSpeed);
  analogWrite(motorLF, moveSpeed);
  analogWrite(motorRB, 0);
  analogWrite(motorLB, 0);
}

void turnLeft()
{
  // Differential Turn: Left back, Right forward
  analogWrite(motorLB, turnSpeed);
  analogWrite(motorRF, turnSpeed);
  analogWrite(motorLF, 0);
  analogWrite(motorRB, 0);
}

void turnRight()
{
  // Differential Turn: Right back, Left forward
  analogWrite(motorRB, turnSpeed);
  analogWrite(motorLF, turnSpeed);
  analogWrite(motorRF, 0);
  analogWrite(motorLB, 0);
}

void stopRobot()
{
  analogWrite(motorRF, 0);
  analogWrite(motorLF, 0);
  analogWrite(motorRB, 0);
  analogWrite(motorLB, 0);
}

// --- Improved Line Follower Logic ---

void lineFollowerMode()
{
  while (true)
  {
    int leftVal = digitalRead(irLineLeft);
    int rightVal = digitalRead(irLineRight);

    if (leftVal == LOW && rightVal == LOW)
    {
      moveForward(); // Both sensors on white
    }
    else if (leftVal == HIGH && rightVal == LOW)
    {
      turnLeft(); // Left sensor on black line, turn left smoothly
    }
    else if (leftVal == LOW && rightVal == HIGH)
    {
      turnRight(); // Right sensor on black line, turn right smoothly
    }
    else
    {
      stopRobot(); // Both on black (Stop or Intersection)
    }
  }
}

void loop()
{
  moveForward();
  delay(2000);
  void stopRobot();
  delay(2000);
  turnLeft();
  delay(2000);
  turnRight();
  delay(2000);
}
