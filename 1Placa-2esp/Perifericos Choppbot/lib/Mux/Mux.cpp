#include <clsPCA9555.h>
#include <Choppbot.h>
#include <Arduino.h>
#include <Wire.h>
#include <Mux.h>

PCA9555 Mux(MuxAdress7);

bool muxInput[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
bool muxOutput[9] = {0, 0, 0, 0, 0, 0, 0, 0};

void muxInit()
{
    Mux.begin();          // iniciando comunicação
    Mux.setClock(100000); // configurando o clock da comunicação
    Mux.pinMode(SwitchSensor1, INPUT);
    Mux.pinMode(SwitchSensor2, INPUT);
    Mux.pinMode(SwitchSensor3, INPUT);
    Mux.pinMode(SwitchSensor4, INPUT);
    Mux.pinMode(SwitchSensor5, INPUT);
    Mux.pinMode(SwitchSensor6, INPUT);
    Mux.pinMode(SwitchSensor7, INPUT);
    Mux.pinMode(SwitchSensor8, INPUT);

    Mux.pinMode(SwitchRelay1, OUTPUT);
    Mux.pinMode(SwitchRelay2, OUTPUT);
    Mux.pinMode(SwitchRelay3, OUTPUT);
    Mux.pinMode(SwitchRelay4, OUTPUT);
    Mux.pinMode(SwitchRelay5, OUTPUT);
    Mux.pinMode(SwitchRelay6, OUTPUT);
    Mux.pinMode(SwitchRelay7, OUTPUT);
    Mux.pinMode(SwitchRelay8, OUTPUT);

    Mux.digitalWrite(SwitchRelay1, muxOutput[1]);
    Mux.digitalWrite(SwitchRelay2, muxOutput[2]);
    Mux.digitalWrite(SwitchRelay3, muxOutput[3]);
    Mux.digitalWrite(SwitchRelay4, muxOutput[4]);
    Mux.digitalWrite(SwitchRelay5, muxOutput[1]);
    Mux.digitalWrite(SwitchRelay6, muxOutput[2]);
    Mux.digitalWrite(SwitchRelay7, muxOutput[7]);
    Mux.digitalWrite(SwitchRelay8, muxOutput[8]);
}

void muxRun()
{
    muxInput[1] = Mux.digitalRead(SwitchSensor1);
    muxInput[2] = Mux.digitalRead(SwitchSensor2);
    muxInput[3] = Mux.digitalRead(SwitchSensor3);
    muxInput[4] = Mux.digitalRead(SwitchSensor4);
    muxInput[5] = Mux.digitalRead(SwitchSensor5);
    muxInput[6] = Mux.digitalRead(SwitchSensor6);
    muxInput[7] = Mux.digitalRead(SwitchSensor7);
    muxInput[8] = Mux.digitalRead(SwitchSensor8);

    Mux.digitalWrite(SwitchRelay1, muxOutput[1]);
    Mux.digitalWrite(SwitchRelay2, muxOutput[2]);
    Mux.digitalWrite(SwitchRelay3, muxOutput[3]);
    Mux.digitalWrite(SwitchRelay4, muxOutput[4]);
    Mux.digitalWrite(SwitchRelay5, muxOutput[1]);
    Mux.digitalWrite(SwitchRelay6, muxOutput[2]);
    Mux.digitalWrite(SwitchRelay7, muxOutput[7]);
    Mux.digitalWrite(SwitchRelay8, muxOutput[8]);

    muxShowData();
}

void muxShowData()
{
    Serial.print("INPUT:");
    Serial.print(muxInput[1]);
    Serial.print("|");
    Serial.print(muxInput[2]);
    Serial.print("|");
    Serial.print(muxInput[3]);
    Serial.print("|");
    Serial.print(muxInput[4]);
    Serial.print("|");
    Serial.print(muxInput[5]);
    Serial.print("|");
    Serial.print(muxInput[6]);
    Serial.print("|");
    Serial.print(muxInput[7]);
    Serial.print("|");
    Serial.print(muxInput[8]);
    Serial.print("|");

    Serial.print(" OUPUT:");
    Serial.print(muxOutput[1]);
    Serial.print("|");
    Serial.print(muxOutput[2]);
    Serial.print("|");
    Serial.print(muxOutput[3]);
    Serial.print("|");
    Serial.print(muxOutput[4]);
    Serial.print("|");
    Serial.print(muxOutput[5]);
    Serial.print("|");
    Serial.print(muxOutput[6]);
    Serial.print("|");
    Serial.print(muxOutput[7]);
    Serial.print("|");
    Serial.print(muxOutput[8]);
    Serial.println("|");
}

bool muxReturnOut(int pin)
{
    return muxOutput[pin];
}

bool muxReturnIn(int pin)
{
    return muxInput[pin];
}

void muxOut(int pin, bool state)
{
    if (pin > 0 and pin <= 8 and state >= 0 and state <= 1)
    {
        muxOutput[pin] = state;
    }
}