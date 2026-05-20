#ifndef STEPMOTOR_H
#define STEPMOTOR_H
void motorRun(float x, float y, float z, float velx, float vely, float velz);
void motorRunIncrement(float x, float y, float z);
float returnPoseX();
float returnPoseY();
float returnPoseZ();
void initMotors();
void homing();
void homing2();
#endif