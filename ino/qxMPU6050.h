#ifndef __QX_MPU6050__
#define __QX_MPU6050__

#include "qxLog.h"

#include <Wire.h>
#include <I2Cdev.h>
#include <Arduino.h>

void qxMPU6050Init(uint8_t MPU6050_I2C_SDA_PIN, uint8_t MPU6050_I2C_SCL_PIN, uint8_t MPU6050_INTERRUPT_PIN);
void qxMPU6050DmpReadyEvent();
int qxMPU6050GetDmpData(double* yaw, double* pitch, double* roll);

#endif