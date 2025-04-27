// Include the required libraries
#include <usb_desc.h>  // Teensy-specific USB descriptor override
#include <usb_rawhid.h>  // For raw HID packet reception

// Motor output pin
const int motorPin = 9;  // PWM capable pin

// Store current force
int currentForce = 0;

// Setup
void setup() {
  Serial.begin(115200);
  
  pinMode(motorPin, OUTPUT);

  // Initialize motor output to 0
  analogWrite(motorPin, 127); // 127 = neutral, centered motor (assuming H-Bridge or similar)
}

// Main loop
void loop() {
  uint8_t buffer[64]; // Max HID report size
  int n = RawHID.recv(buffer, 0);  // Receive raw HID report (non-blocking)

  if (n > 0) {
    parseFFBReport(buffer, n);
  }

  applyMotorForce(currentForce);
}

// Parse incoming HID PID Force Feedback report
void parseFFBReport(uint8_t* data, int length) {
  Serial.println("Received FFB Packet");

  // Simplified: assume the packet has:
  // byte 0 = Report ID
  // byte 1 = Force Magnitude (0-255)
  uint8_t reportId = data[0];
  uint8_t magnitude = data[1];

  Serial.print("Report ID: ");
  Serial.println(reportId);
  Serial.print("Force Magnitude: ");
  Serial.println(magnitude);

  // Map 0-255 -> -127 to 127
  currentForce = (int)magnitude - 127;
}

// Apply motor PWM based on force
void applyMotorForce(int force) {
  // Map force to PWM output
  // Assume 127 is center (no force), 0 is full reverse, 255 is full forward
  int pwmValue = constrain(127 + force, 0, 255);
  analogWrite(motorPin, pwmValue);
}
