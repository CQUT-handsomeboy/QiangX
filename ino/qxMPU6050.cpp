#include "qxMPU6050.h"
#include <MPU6050_6Axis_MotionApps20.h>

MPU6050 mpu;
Quaternion q;
VectorFloat gravity;
bool dmpReady = false;
uint8_t mpuInterruptStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];
float ypr[3];
volatile bool mpuInterruptFlag = false;

void qxMPU6050Init(uint8_t MPU6050_I2C_SDA_PIN, uint8_t MPU6050_I2C_SCL_PIN, uint8_t MPU6050_INTERRUPT_PIN) {
  Wire.begin(MPU6050_I2C_SDA_PIN, MPU6050_I2C_SCL_PIN);

  pinMode(MPU6050_INTERRUPT_PIN, INPUT);

  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);

  attachInterrupt(digitalPinToInterrupt(MPU6050_INTERRUPT_PIN), qxMPU6050DmpReadyEvent, RISING);

  mpuInterruptStatus = mpu.getIntStatus();

  dmpReady = true;
  packetSize = mpu.dmpGetFIFOPacketSize();
}

void qxMPU6050DmpReadyEvent() {
  mpuInterruptFlag = true;
}

int qxMPU6050GetDmpData(double* yaw, double* pitch, double* roll) {
  if (!dmpReady)
    return -1;
  while (!mpuInterruptFlag && fifoCount < packetSize) {
    fifoCount = mpu.getFIFOCount();
  }

  mpuInterruptFlag = false;
  mpuInterruptStatus = mpu.getIntStatus();

  fifoCount = mpu.getFIFOCount();

  if ((mpuInterruptStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();
    return -2;
  } else if (mpuInterruptStatus & 0x02) {
    while (fifoCount < packetSize)
      fifoCount = mpu.getFIFOCount();

    mpu.getFIFOBytes(fifoBuffer, packetSize);

    fifoCount -= packetSize;
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    *yaw = ypr[0] * 180 / M_PI;
    *pitch = ypr[1] * 180 / M_PI;
    *roll = ypr[2] * 180 / M_PI;

    return 0;
  }
}
