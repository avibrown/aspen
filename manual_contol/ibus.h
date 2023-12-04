#include "HardwareSerial.h"
#ifndef IBUS_H
#define IBUS_H

#include <Arduino.h>
#include <ODriveArduino.h>
#include <IBusBM.h>

extern ODriveArduino odrive;

IBusBM Ibus;
bool armedToggle = false;

void IbusInit() {
    Ibus.begin(Serial1);
}

int regReadIbusChannel(int channel) {
    return Ibus.readChannel(channel);
}

bool boolReadIbusChannel(int channel) {
    return map(Ibus.readChannel(channel), 1000, 2000, 0, 1);
}

void calibrateMotor(int motorIndex) {
  int requestedState = AXIS_STATE_ENCODER_OFFSET_CALIBRATION;
  odrive.run_state(motorIndex, requestedState, false, 100);
}

void enterClosedLoopControl(int motorIndex) {
  int requestedState = AXIS_STATE_CLOSED_LOOP_CONTROL;
  odrive.run_state(motorIndex, requestedState, false);
}

void processIbus() {
    bool armedState = boolReadIbusChannel(5);
    bool emergency = boolReadIbusChannel(4);
  
    int velocity = regReadIbusChannel(1);
    float rightMappedVelocity = (float)map(velocity, 1000, 2000, -120, 120) / 100.0;
    float leftMappedVelocity = (float)map(velocity, 1000, 2000, 120, -120) / 100.0;
  
    int turnVelocity = regReadIbusChannel(0);
    float mappedTurnVelocity = (float)map(turnVelocity, 1000, 2000, -100, 100) / 100.0;
  
    rightMappedVelocity = rightMappedVelocity - mappedTurnVelocity;
    leftMappedVelocity = leftMappedVelocity - mappedTurnVelocity;

    if (abs(rightMappedVelocity) < 0.03) {
      rightMappedVelocity = 0.0;
    }

if (abs(leftMappedVelocity) < 0.03) {
      leftMappedVelocity = 0.0;
    }

    if (armedState == true && !emergency) {
      odrive.SetVelocity(0, leftMappedVelocity);
      odrive.SetVelocity(1, rightMappedVelocity);

      Serial.print("leftMappedVelocity: "); Serial.print(leftMappedVelocity); Serial.print("   rightMappedVelocity: "); Serial.println(rightMappedVelocity);
     }

    else if (armedState == false && !emergency) {
      if (!armedToggle){
          odrive.SetVelocity(0, 0);
          odrive.SetVelocity(1, 0);
          armedToggle = true;
        }
      }

    if (emergency == true) {
        odrive.SetVelocity(0, 0);
        odrive.SetVelocity(1, 0);
      }

    
}

#endif
