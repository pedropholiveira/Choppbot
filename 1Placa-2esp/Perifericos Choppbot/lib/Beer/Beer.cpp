#include <Choppbot.h>
#include <Arduino.h>
#include <Beer.h>
#include <Mux.h>

static bool stateFlux1 = 0, laststateFlux1 = 0;
static bool stateFlux2 = 0, laststateFlux2 = 0;

static float contFlux1 = 0, totalFlux1 = 0, copoFlux1 = 0, tempFlux1 = 0, timeFlux1 = 0, litrosFlux1 = 0;
static float contFlux2 = 0, totalFlux2 = 0, copoFlux2 = 0, tempFlux2 = 0, timeFlux2 = 0, tempoFlux2 = 0, litrosFlux2 = 0;

static bool sangria = 0;

static float contGas = 0, timegas = 0;

void flux1(bool input)
{
    if (input != laststateFlux1)
    {
        contFlux1++;
        laststateFlux1 = input;
    }
    totalFlux1 = ((contFlux1 / 450) / 2);
}

void flux2(bool input)
{
    if (input != laststateFlux2)
    {
        contFlux2++;
        laststateFlux2 = input;
    }
    totalFlux2 = ((contFlux2 / 450) / 2);
}

void fluxRun(int pinflux1, int pinflux2)
{
    flux1(muxReturnIn(pinflux1));
    flux2(muxReturnIn(pinflux2));

    if ((millis() - tempFlux1 >= timeFlux1 or totalFlux1 - litrosFlux1 > copoFlux1) and muxReturnOut(SolenoideA) == 1 and sangria == 0)
    {
        muxOut(SolenoideA, 0);
    }

    if ((millis() - tempFlux2 >= timeFlux2))
    {
        if (totalFlux2 == litrosFlux2)
        {
            muxOut(SolenoideB, 0);
        }
        else
        {
            litrosFlux2 = totalFlux2;
            tempFlux2 = millis();
            timeFlux2 = tempoFlux2;
        }
    }

    if (muxReturnOut(gas) == 1 and millis() - contGas >= timegas)
    {
        muxOut(gas, 0);
    }
}

float returnFlux(int valve)
{
    if (valve == SolenoideA)
    {
        return totalFlux1;
    }
    if (valve == SolenoideB)
    {
        return totalFlux2;
    }
    return 0;
}

void triggerFlux1(float copo, float time, bool state, bool sangrar)
{
    totalFlux1 = 0;
    contFlux1 = 0;
    litrosFlux1 = totalFlux1;
    copoFlux1 = copo;
    sangria = sangrar;
    timeFlux1 = time;
    tempFlux1 = millis();
    muxOut(SolenoideA, state);
}

void triggerFlux2(float copo, float time, float time2, bool state)
{
    totalFlux2 = 0;
    contFlux2 = 0;
    litrosFlux2 = totalFlux2;
    copoFlux2 = copo;
    timeFlux2 = time;
    tempoFlux2 = time2;
    tempFlux2 = millis();
    muxOut(SolenoideB, state);
}

void triggerGas(float time, bool state)
{
    timegas = time;
    contGas = millis();
    muxOut(gas, state);
}
