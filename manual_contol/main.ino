#include <HardwareSerial.h>
#include <ODriveArduino.h>
#include "ibus.h"

HardwareSerial& odriveSerial = Serial3;
ODriveArduino odrive(odriveSerial);

void setup() {
  Serial.begin(115200);
  setupOdriveSerialCommunication();
  setupIbus();
  initClosedLoopControl();
    odrive.SetVelocity(0, 0);
    odrive.SetVelocity(1, 0);
}

void loop() {
  processIbus();

  delay(1);
}

void setupOdriveSerialCommunication() {
  odriveSerial.begin(115200);
}

void setupIbus() {
  IbusInit();
}

void initClosedLoopControl() {
    
  for (int motorIndex = 0; motorIndex < 2; ++motorIndex) {
    enterClosedLoopControl(motorIndex);
    Serial.print("Closed loop: "); Serial.println(motorIndex);
  }
}
