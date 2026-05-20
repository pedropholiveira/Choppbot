#include <ESP32Servo.h>
#include <Choppbot.h>
#include <Arduino.h>
#include <Grab.h>

Servo garra;
static int pos = 0;

void initGrab()
{
    garra.attach(Servo4);
}
int returnPoesgrab()
{
    return pos;
}
void triggergrab(int angle)
{
    pos = angle;
    garra.write(pos);
}
void byebye(int min, int max, int ciclos, int home)
{
    for (int i = 0; i < ciclos; i++)
    {
        triggergrab(min);
        delay(500);
        triggergrab(max);
        delay(500);
    }
    triggergrab(home);
}