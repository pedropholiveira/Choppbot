#include <Choppbot.h>
#include <Arduino.h>
#include <CoreOne.h>
#include <CoreTwo.h>
#include <Routes.h>
#include <Rede.h>
#include <Temp.h>
#include <Grab.h>
#include <RTOS.h>
#include <Cup.h>
#include <Mux.h>

TaskHandle_t xCoreOne;
TaskHandle_t xCoreTwo;

void setup()
{
  Serial.begin(115200);
  muxInit();
  initCup();
  initGrab();
  initTemp();
  initConection();
  routesCreates();
  xTaskCreatePinnedToCore(CoreOne, "coreOne", 10000, NULL, 5, &xCoreOne, 1);
  xTaskCreatePinnedToCore(CoreTwo, "CoreTwo", 10000, NULL, 5, &xCoreTwo, 0);
}

void loop()
{
}