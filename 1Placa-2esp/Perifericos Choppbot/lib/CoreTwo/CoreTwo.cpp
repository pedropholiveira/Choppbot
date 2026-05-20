#include <Choppbot.h>
#include <CoreTwo.h>
#include <Arduino.h>
#include <Routes.h>
#include <Rede.h>
#include <Grab.h>
#include <Beer.h>
#include <Cup.h>
#include <Mux.h>

void CoreTwo(void *pvParameters)
{
    while (1)
    {
        muxRun();
        fluxRun(FluxA, FluxB);
    }
}