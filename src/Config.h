#ifndef CONFIG_H
#define CONFIG_H

// -----------------------------
// Pin Definitions
// -----------------------------
#define motorRB 6  // Servo motor pin
#define motorRF 9  // Servo motor pin
#define motorLF 10 // Servo motor pin
#define motorLB 11 // Servo motor pin

#define irLine_PIN A0  // Near Sensor pin (Obstacle Detection)
#define irLine_PIN1 A1 // Sensor1 pin (Far Left)
#define irLine_PIN2 A2 // Sensor2 pin (Near Left)
#define irLine_PIN3 A3 // Sensor3 pin (Center)
#define irLine_PIN4 A4 // Sensor4 pin (Near Right)
#define irLine_PIN5 A5 // Sensor5 pin (Far Right)

// -----------------------------
// Speed Constants (0 to 255)
// -----------------------------
#define moveSpeed 255 // Normal speed for moving forward
#define turnSpeed 126 // Lower speed for smooth turning

#endif