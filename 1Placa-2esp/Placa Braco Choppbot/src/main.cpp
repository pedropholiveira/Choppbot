#include <StepMotor.h>
#include <Choppbot.h>
#include <Arduino.h>
#include <Routes.h>
#include <Rede.h>
#include <Grab.h>
#include <Cup.h>

void setup()
{
  Serial.begin(115200);
  initMotors();
  initConection();
  initGrab();
  initCup();
  homing2();
  routesCreates();
}

void loop()
{
  checkConection();
  serverRun();
}