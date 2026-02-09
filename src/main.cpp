#include <Arduino.h>
#include "Config.h"

// ==================================================
// Sensors (A1-A5 only for line)
// ==================================================
const uint8_t sensorPins[] = {
    irLine_PIN1,
    irLine_PIN2,
    irLine_PIN3,
    irLine_PIN4,
    irLine_PIN5};

const int SENSOR_COUNT = 5;

// reversed weights (fix direction)
int weights[] = {3, 2, 0, -2, -3};

// ==================================================
// PID Constants
// ==================================================
float Kp = 22;
float Ki = 0.8; // NEW (small on purpose)
float Kd = 18;

float integral = 0;
float lastError = 0;

int baseSpeed = 120;

// ==================================================
void setup()
{
  pinMode(motorRF, OUTPUT);
  pinMode(motorRB, OUTPUT);
  pinMode(motorLF, OUTPUT);
  pinMode(motorLB, OUTPUT);

  for (int i = 0; i < SENSOR_COUNT; i++)
    pinMode(sensorPins[i], INPUT);

  pinMode(irLine_PIN, INPUT); // obstacle
}

// ==================================================
// Read line position
// ==================================================
float readLineError()
{
  long sum = 0;
  int count = 0;

  for (int i = 0; i < SENSOR_COUNT; i++)
  {
    if (digitalRead(sensorPins[i]) == HIGH)
    {
      sum += weights[i];
      count++;
    }
  }

  if (count == 0)
    return lastError;

  return (float)sum / count;
}

// ==================================================
// Obstacle handling (A0)
// ==================================================
bool obstacleDetected()
{
  return digitalRead(irLine_PIN) == HIGH;
}

// ==================================================
void moveSmoothly(int left, int right)
{
  left = constrain(left, -255, 255);
  right = constrain(right, -255, 255);

  // Left
  if (left >= 0)
  {
    analogWrite(motorLF, left);
    analogWrite(motorLB, 0);
  }
  else
  {
    analogWrite(motorLF, 0);
    analogWrite(motorLB, -left);
  }

  // Right
  if (right >= 0)
  {
    analogWrite(motorRF, right);
    analogWrite(motorRB, 0);
  }
  else
  {
    analogWrite(motorRF, 0);
    analogWrite(motorRB, -right);
  }
}

// ==================================================
void stopRobot()
{
  analogWrite(motorRF, 0);
  analogWrite(motorRB, 0);
  analogWrite(motorLF, 0);
  analogWrite(motorLB, 0);
}

// ==================================================
void loop()
{
  // --------- OBSTACLE MODE ----------
  if (obstacleDetected())
  {
    stopRobot();
    return; // skip PID
  }

  // --------- PID CONTROL ------------
  float error = readLineError();

  // Integral (anti-windup clamp)
  integral += error;
  integral = constrain(integral, -50, 50);

  float correction =
      (Kp * error) +
      (Ki * integral) +
      (Kd * (error - lastError));

  lastError = error;

  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  moveSmoothly(leftSpeed, rightSpeed);
}
