#include <DallasTemperature.h>
#include <Choppbot.h>
#include <Arduino.h>
#include <OneWire.h>
#include <Temp.h>

// GPIO where the DS18B20 is connected to
const int oneWireBus = Temp;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature chop(&oneWire);

void initTemp()
{
    Serial.begin(115200);
    chop.begin();
}

float redTemp()
{
    chop.requestTemperatures();
    float temperatureC = chop.getTempCByIndex(0);
    float temperatureF = chop.getTempFByIndex(0);
    // Serial.print(temperatureC);
    // Serial.println("ºC");
    // Serial.print(temperatureF);
    // Serial.println("ºF");
    // delay(5000);
    return temperatureC;
}