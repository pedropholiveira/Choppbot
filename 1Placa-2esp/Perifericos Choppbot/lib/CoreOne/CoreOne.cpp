#include <Choppbot.h>
#include <CoreOne.h>
#include <Routes.h>
#include <Rede.h>
#include <RTOS.h>
void CoreOne(void *pvParameters)
{
    while (1)
    {
        checkConection();
        serverRun();
        vTaskDelay(1);
    }
}