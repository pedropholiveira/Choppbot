#include <ArduinoJson.h>
#include <WebServer.h>
#include <Choppbot.h>
#include <Arduino.h>
#include <Routes.h>
#include <Beer.h>
#include <Temp.h>
#include <Rede.h>
#include <Grab.h>
#include <Cup.h>
#include <Mux.h>

WebServer server(80);
StaticJsonDocument<300> document;
char buffer[300];

void routesCreates()
{
    server.on(returnBoard, returnALL);

    // server.on(grabWrite, HTTP_POST, triggerGrab);
    // server.on(grabBye, HTTP_POST, byegrab);

    server.on(beerAservice, HTTP_POST, triggerBeerA);
    server.on(beerBservice, HTTP_POST, triggerBeerB);

    // server.on(cupTest, HTTP_POST, cup_Test);
    // server.on(cupService, HTTP_POST, cup_Service);
    // server.on(cupWrite, HTTP_POST, cup_Write);

    server.on(ledtrigger, HTTP_POST, triggerLed);

    server.on(gastrigger, HTTP_POST, triggergas);

    server.begin();
}

void createJson()
{
    document.clear();

    JsonObject beerA = document.createNestedObject("beerA");
    beerA["fluxA"] = returnFlux(1);
    beerA["state_valve"] = muxReturnOut(SolenoideA);
    // beerA["temp"] = redTemp();

    JsonObject beerB = document.createNestedObject("beerB");
    beerB["fluxB"] = returnFlux(2);
    beerB["state_valve"] = muxReturnOut(SolenoideB);

    JsonObject cup = document.createNestedObject("dispenser");
    cup["cup"] = muxReturnIn(SensorDispenser);

    JsonObject grab = document.createNestedObject("grab");
    // grab["pose"] = returnPoesgrab();
    grab["grab_cup"] = !muxReturnIn(SensorGarra1);
    grab["grab_chopp"] = !muxReturnIn(SensorGarra2);

    JsonObject Giroflex = document.createNestedObject("giroflex");
    Giroflex["state1"] = muxReturnOut(Giroled1);
    Giroflex["state2"] = muxReturnOut(Giroled2);

    JsonObject Gas = document.createNestedObject("gas");
    Gas["state"] = muxReturnOut(gas);

    serializeJson(document, buffer);
}
void serverRun()
{
    server.handleClient();
}

void returnALL()
{
    createJson();
    server.send(200, "application/json", buffer);
}

void triggerBeerA()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    triggerFlux1(document["cup"], document["time"], document["valve"], document["sangria"]);
    createJson();
    server.send(200, "application/json", buffer);
}

void triggerBeerB()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    triggerFlux2(document["cup"], document["init_time"], document["time"], document["valve"]);
    createJson();
    server.send(200, "application/json", buffer);
}

void cup_Test()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    testCup(document["min"], document["max"]);
    createJson();
    server.send(200, "application/json", buffer);
}

void cup_Service()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    serviceCup(document["min"], document["max"], muxReturnIn(SensorDispenser));
    createJson();
    server.send(200, "application/json", buffer);
}

void cup_Write()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    writeCup(document["angle"]);
    createJson();
    server.send(200, "application/json", buffer);
}

void triggerLed()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    muxOut(Giroled1, document["state1"]);
    muxOut(Giroled2, document["state2"]);
    createJson();
    server.send(200, "application/json", buffer);
}

void triggerGrab()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    triggergrab(document["angle"]);
    createJson();
    server.send(200, "application/json", buffer);
}

void byegrab()
{
    if (server.hasArg("plain") == false)
    {
        // handle error here
    }
    String body = server.arg("plain");
    deserializeJson(document, body);
    byebye(document["min"], document["max"], document["cycles"], document["home"]);
    createJson();
    server.send(200, "application/json", buffer);
}

void triggergas()
{
    if (server.hasArg("plain") == false)
    {
        // handle error here
    }
    String body = server.arg("plain");
    deserializeJson(document, body);
    triggerGas(document["time"], document["state"]);
    createJson();
    server.send(200, "application/json", buffer);
}