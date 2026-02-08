#ifndef CONFIG_H
#define CONFIG_H

// -----------------------------
// Pin Definitions
// -----------------------------
#define motorRB 6  // Servo motor pin
#define motorRF 9  // Servo motor pin
#define motorLF 10 // Servo motor pin
#define motorLB 11 // Servo motor pin

#define irLine_PIN A0 // Near Sensor pin
#define irLine_PIN A1 // Sensor1 pin
#define irLine_PIN A2 // Sensor2 pin
#define irLine_PIN A3 // Sensor3 pin
#define irLine_PIN A4 // Sensor4 pin
#define irLine_PIN A5 // Sensor5 pin

// -----------------------------
// Speed Constants (0 to 255)
// -----------------------------
#define moveSpeed 255 // Normal speed for moving forward
#define turnSpeed 122 // Lower speed for smooth turning

#endif