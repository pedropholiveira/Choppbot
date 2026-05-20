#include <ESP32Servo.h>
#include <Choppbot.h>
#include <Arduino.h>
#include <Cup.h>

Servo copo;

void initCup()
{
    copo.attach(Servo3);
}

void serviceCup(int min, int max, bool sensor)
{
    if (sensor == 1)
    {
        copo.write(max);
        delay(1000);
        copo.write(min);
        delay(1000);
    }
}

void testCup(int min, int max)
{
    copo.write(max);
    delay(1000);
    copo.write(min);
    delay(1000);
}

void writeCup(int angle)
{
    copo.write(angle);
}